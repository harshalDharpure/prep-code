"""Deterministic behavior and failure-path tests for the interview workbook."""
import asyncio
import hashlib
import hmac
import math
import tempfile
import unittest
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

from ai_roles_practical_solutions import (
    LRUCache, TTLCache, TokenBucket, SlidingWindowLimiter, EventProcessor,
    run_bounded, retry, CircuitBreaker, CircuitOpen, Trie, TopKCounter,
    merge_events, chunk_document, Principal, Document, retrieve,
    retrieval_metrics, PromptRegistry, truncate_conversation, FeatureStore,
    analyze_logs, verify_webhook, ModelSpec, ModelRouter,
)


class Clock:
    def __init__(self):
        self.now = 0.0

    def __call__(self):
        return self.now


def timeout():
    raise TimeoutError("simulated transient failure")


class CacheTests(unittest.TestCase):
    def test_lru_recency(self):
        cache = LRUCache(2)
        cache.put("a", 1)
        cache.put("b", 2)
        self.assertEqual(cache.get("a"), 1)
        cache.put("c", 3)
        with self.assertRaises(KeyError):
            cache.get("b")
        self.assertEqual(cache.get("c"), 3)

    def test_lru_update_and_none(self):
        cache = LRUCache(1)
        cache.put("a", 1)
        cache.put("a", None)
        self.assertIsNone(cache.get("a"))
        with self.assertRaises(ValueError):
            LRUCache(0)

    def test_ttl_exact_boundary(self):
        clock = Clock()
        cache = TTLCache(2, clock)
        cache.put("a", 1, 5)
        clock.now = 4.999
        self.assertEqual(cache.get("a"), 1)
        clock.now = 5
        with self.assertRaises(KeyError):
            cache.get("a")

    def test_ttl_update_cleanup_capacity(self):
        clock = Clock()
        cache = TTLCache(2, clock)
        cache.put("a", 1, 1)
        cache.put("b", 2, 10)
        clock.now = 2
        cache.put("c", 3, 10)
        self.assertEqual(cache.get("b"), 2)
        cache.put("b", 4, 20)
        clock.now = 12
        self.assertEqual(cache.get("b"), 4)
        with self.assertRaises(KeyError):
            cache.get("c")
        with self.assertRaises(ValueError):
            cache.put("x", 1, float("nan"))


class LimiterTests(unittest.TestCase):
    def test_token_refill_and_cap(self):
        clock = Clock()
        bucket = TokenBucket(2, 2, clock)
        self.assertTrue(bucket.allow(2))
        self.assertFalse(bucket.allow())
        clock.now = 0.5
        self.assertTrue(bucket.allow())
        clock.now = 100
        self.assertTrue(bucket.allow(2))
        self.assertFalse(bucket.allow())
        with self.assertRaises(ValueError):
            bucket.allow(3)

    def test_token_atomic_admission(self):
        bucket = TokenBucket(10, 1, Clock())
        with ThreadPoolExecutor(max_workers=8) as pool:
            accepted = list(pool.map(lambda _: bucket.allow(), range(100)))
        self.assertEqual(sum(accepted), 10)

    def test_sliding_boundary(self):
        clock = Clock()
        limiter = SlidingWindowLimiter(2, 10, clock)
        self.assertTrue(limiter.allow())
        clock.now = 1
        self.assertTrue(limiter.allow())
        clock.now = 9
        self.assertFalse(limiter.allow())
        clock.now = 10
        self.assertTrue(limiter.allow())
        self.assertFalse(limiter.allow())

    def test_invalid_limits(self):
        with self.assertRaises(ValueError):
            TokenBucket(0, 1)
        with self.assertRaises(ValueError):
            SlidingWindowLimiter(1, 0)


class IdempotencyTests(unittest.TestCase):
    def test_replay_survives_reopen_and_scopes_tenant(self):
        with tempfile.TemporaryDirectory() as directory:
            path = str(Path(directory) / "events.db")
            first = EventProcessor(path)
            result = first.process("a", "event1", {"name": "Alice"})
            first.close()
            second = EventProcessor(path)
            try:
                self.assertEqual(second.process("a", "event1", {"name": "Alice"}), result)
                other = second.process("b", "event1", {"name": "Alice"})
                self.assertNotEqual(other, result)
                self.assertEqual(second.db.execute("SELECT COUNT(*) FROM records").fetchone()[0], 2)
            finally:
                second.close()

    def test_conflict_rolls_back(self):
        processor = EventProcessor(":memory:")
        try:
            processor.process("a", "e", {"name": "Alice"})
            with self.assertRaises(ValueError):
                processor.process("a", "e", {"name": "Bob"})
            self.assertFalse(processor.db.in_transaction)
            self.assertEqual(processor.db.execute("SELECT COUNT(*) FROM records").fetchone()[0], 1)
            processor.process("a", "e2", {"name": "Bob"})
        finally:
            processor.close()

    def test_database_failure_does_not_leave_orphan_mutation(self):
        processor = EventProcessor(":memory:")
        try:
            processor.db.execute("""CREATE TRIGGER reject_event BEFORE INSERT ON events
                BEGIN SELECT RAISE(ABORT, 'injected failure'); END""")
            with self.assertRaises(Exception):
                processor.process("a", "e", {"name": "Alice"})
            self.assertEqual(processor.db.execute("SELECT COUNT(*) FROM records").fetchone()[0], 0)
            self.assertFalse(processor.db.in_transaction)
        finally:
            processor.close()

    def test_concurrent_connections_create_one_record(self):
        with tempfile.TemporaryDirectory() as directory:
            path = str(Path(directory) / "events.db")
            setup = EventProcessor(path)
            setup.close()

            def process(_):
                worker = EventProcessor(path)
                try:
                    return worker.process("a", "same", {"name": "Alice"})
                finally:
                    worker.close()

            with ThreadPoolExecutor(max_workers=4) as pool:
                results = list(pool.map(process, range(12)))
            self.assertTrue(all(r == results[0] for r in results))
            check = EventProcessor(path)
            try:
                self.assertEqual(check.db.execute("SELECT COUNT(*) FROM records").fetchone()[0], 1)
            finally:
                check.close()


class QueueTests(unittest.IsolatedAsyncioTestCase):
    async def test_order_concurrency_and_failure(self):
        active = peak = 0

        async def worker(value):
            nonlocal active, peak
            active += 1
            peak = max(peak, active)
            try:
                await asyncio.sleep(0)
                if value == 3:
                    raise ValueError("bad item")
                return value * 2
            finally:
                active -= 1

        results = await run_bounded(range(8), worker, workers=2, max_pending=1)
        self.assertLessEqual(peak, 2)
        self.assertEqual(results[4], (True, 8))
        self.assertFalse(results[3][0])
        self.assertIsInstance(results[3][1], ValueError)
        self.assertEqual(len(results), 8)

    async def test_empty_and_bad_limits(self):
        async def identity(value):
            return value
        self.assertEqual(await run_bounded([], identity), [])
        with self.assertRaises(ValueError):
            await run_bounded([], identity, workers=0)

    async def test_cancellation_cleans_up_worker(self):
        entered, exited = asyncio.Event(), asyncio.Event()

        async def worker(value):
            entered.set()
            try:
                await asyncio.Event().wait()
            finally:
                exited.set()

        task = asyncio.create_task(run_bounded(range(10), worker, 1, 1))
        await asyncio.wait_for(entered.wait(), 1)
        task.cancel()
        with self.assertRaises(asyncio.CancelledError):
            await task
        self.assertTrue(exited.is_set())

    async def test_producer_failure_propagates(self):
        def bad_items():
            yield 1
            raise ValueError("iterator failed")

        async def worker(value):
            return value

        with self.assertRaisesRegex(ValueError, "iterator failed"):
            await run_bounded(bad_items(), worker, 1, 1)


class ResilienceTests(unittest.TestCase):
    def test_retry_eventual_success_and_jitter(self):
        calls, sleeps = [], []

        def operation():
            calls.append(1)
            if len(calls) < 3:
                raise TimeoutError()
            return "ok"

        self.assertEqual(retry(operation, base=1, cap=1.5, sleep=sleeps.append,
                               rng=lambda: 0.5), "ok")
        self.assertEqual(sleeps, [0.5, 0.75])
        self.assertEqual(len(calls), 3)

    def test_retry_exhaustion_and_terminal_errors(self):
        sleeps = []
        with self.assertRaises(TimeoutError):
            retry(timeout, attempts=2, sleep=sleeps.append, rng=lambda: 0)
        self.assertEqual(len(sleeps), 1)

        def invalid():
            raise ValueError("terminal")
        with self.assertRaises(ValueError):
            retry(invalid, sleep=lambda _: self.fail("must not sleep"))

    def test_circuit_open_and_recovery(self):
        clock = Clock()
        breaker = CircuitBreaker(2, 5, clock)
        for _ in range(2):
            with self.assertRaises(TimeoutError):
                breaker.call(timeout)
        with self.assertRaises(CircuitOpen):
            breaker.call(lambda: self.fail("must fail fast"))
        clock.now = 5
        self.assertEqual(breaker.call(lambda: "ok"), "ok")
        self.assertIsNone(breaker.opened_at)

    def test_failed_probe_reopens(self):
        clock = Clock()
        breaker = CircuitBreaker(1, 5, clock)
        with self.assertRaises(TimeoutError):
            breaker.call(timeout)
        clock.now = 5
        with self.assertRaises(TimeoutError):
            breaker.call(timeout)
        clock.now = 9
        with self.assertRaises(CircuitOpen):
            breaker.call(lambda: "ok")

    def test_business_error_is_not_dependency_failure(self):
        breaker = CircuitBreaker(1)
        def invalid():
            raise ValueError("bad request")
        with self.assertRaises(ValueError):
            breaker.call(invalid)
        self.assertEqual(breaker.call(lambda: 1), 1)


class AlgorithmTests(unittest.TestCase):
    def test_trie_order_duplicates_and_empty(self):
        trie = Trie()
        for word in ["cat", "car", "cart", "dog", "car", ""]:
            trie.insert(word)
        self.assertEqual(trie.autocomplete("ca", 2), ["car", "cart"])
        self.assertEqual(trie.autocomplete("z"), [])
        self.assertEqual(trie.autocomplete("", 1), [""])
        self.assertEqual(trie.autocomplete("", 0), [])

    def test_topk_ties_and_bounds(self):
        counter = TopKCounter()
        for item in ["b", "a", "b", "a", "c"]:
            counter.add(item)
        self.assertEqual(counter.top(2), [("a", 2), ("b", 2)])
        self.assertEqual(counter.top(0), [])
        self.assertEqual(len(counter.top(100)), 3)

    def test_merge_ties_do_not_compare_payloads(self):
        streams = [[(1, {"a": 1}), (3, {"a": 3})], [], [(1, {"b": 1})]]
        self.assertEqual(list(merge_events(streams)),
                         [(1, {"a": 1}), (1, {"b": 1}), (3, {"a": 3})])

    def test_merge_rejects_unsorted_input(self):
        with self.assertRaises(ValueError):
            list(merge_events([[(2, "a"), (1, "b")]]))

    def test_chunk_sentence_and_long_sentence(self):
        count = lambda text: len(text.split())
        self.assertEqual(chunk_document("One two. Three four five.", 3, count),
                         ["One two.", "Three four five."])
        chunks = chunk_document("a b c d e", 2, count)
        self.assertEqual(chunks, ["a b", "c d", "e"])
        self.assertEqual(chunk_document("", 2, count), [])

    def test_chunk_actual_join_cost_and_oversized_word(self):
        chunks = chunk_document("aa bb cc", 5, len)
        self.assertEqual(chunks, ["aa bb", "cc"])
        self.assertTrue(all(len(c) <= 5 for c in chunks))
        with self.assertRaises(ValueError):
            chunk_document("toolong", 3, len)


class RetrievalTests(unittest.TestCase):
    def setUp(self):
        self.principal = Principal("a", "alice")
        self.docs = [Document("ok", "a", frozenset({"alice"}), "reset password"),
                     Document("other", "b", frozenset({"alice"}), "reset password"),
                     Document("denied", "a", frozenset({"bob"}), "reset password")]

    def test_permission_filters(self):
        self.assertEqual([d.id for d in retrieve(self.principal, "password", self.docs)], ["ok"])
        self.assertEqual(retrieve(self.principal, "", self.docs), [])

    def test_authoritative_revocation_and_error(self):
        self.assertEqual(retrieve(self.principal, "password", self.docs,
                                  authorize=lambda p, d: False), [])
        def unavailable(p, d):
            raise ConnectionError("authorization unavailable")
        with self.assertRaises(ConnectionError):
            retrieve(self.principal, "password", self.docs, authorize=unavailable)

    def test_duplicate_ids_rejected(self):
        with self.assertRaises(ValueError):
            retrieve(self.principal, "password", [self.docs[0], self.docs[0]])

    def test_metrics_worked_example(self):
        result = retrieval_metrics(["b", "x", "a"], {"a": 2, "b": 1}, 2)
        self.assertEqual(result["precision"], 0.5)
        self.assertEqual(result["recall"], 0.5)
        self.assertEqual(result["mrr"], 1)
        self.assertAlmostEqual(result["ndcg"], 1 / (2 + 1 / math.log2(3)))

    def test_metrics_perfect_empty_and_duplicates(self):
        self.assertEqual(retrieval_metrics(["a", "b"], {"a": 2, "b": 1}, 2)["ndcg"], 1)
        self.assertEqual(retrieval_metrics([], {}, 3)["recall"], 0)
        self.assertEqual(retrieval_metrics(["a"], {"a": 1}, 2)["precision"], 0.5)
        with self.assertRaises(ValueError):
            retrieval_metrics(["a", "a"], {"a": 1}, 2)


class StateTests(unittest.TestCase):
    def test_prompt_immutability_activation_and_rollback(self):
        registry = PromptRegistry()
        first = registry.register("p", "v1", "one")
        self.assertEqual(registry.register("p", "v1", "one"), first)
        registry.register("p", "v2", "two")
        registry.activate("p", "v2")
        self.assertEqual(registry.get("p").template, "two")
        registry.activate("p", "v1")
        with self.assertRaises(ValueError):
            registry.register("p", "v1", "changed")
        with self.assertRaises(KeyError):
            registry.activate("p", "missing")
        self.assertEqual(registry.get("p"), first)

    def test_context_preserves_atomic_groups(self):
        system, current = [{"text": "system"}], [{"text": "current"}]
        older = [{"text": "old"}]
        tool_group = [{"text": "call"}, {"text": "result"}]
        self.assertEqual(truncate_conversation(system, [older, tool_group], current,
                                               5, 1, len), system + tool_group + current)
        self.assertEqual(truncate_conversation(system, [older, tool_group], current,
                                               4, 1, len), system + current)

    def test_context_protected_overflow(self):
        with self.assertRaises(ValueError):
            truncate_conversation([{}], [], [{}], 2, 1, len)

    def test_feature_point_in_time_and_tenant(self):
        store = FeatureStore()
        store.put("a", "u", "f", 10, 10, 1)
        store.put("a", "u", "f", 12, 20, 2)
        self.assertEqual(store.get("a", "u", "f", 15).value, 1)
        self.assertEqual(store.get("a", "u", "f", 21).value, 2)
        with self.assertRaises(KeyError):
            store.get("b", "u", "f", 21)
        with self.assertRaises(KeyError):
            store.get("a", "u", "f", 9)

    def test_feature_staleness_and_conflict(self):
        store = FeatureStore()
        store.put("a", "u", "f", 10, 11, 1)
        store.put("a", "u", "f", 10, 11, 1)
        with self.assertRaises(ValueError):
            store.put("a", "u", "f", 10, 11, 2)
        with self.assertRaises(KeyError):
            store.get("a", "u", "f", 20, max_age=5)


class LogsAndSignatureTests(unittest.TestCase):
    def test_percentiles_and_failure_latency(self):
        rows = [{"latency_ms": i, "ok": i != 100} for i in range(1, 101)]
        result = analyze_logs(rows)
        self.assertEqual((result["p50_ms"], result["p95_ms"], result["p99_ms"]), (50, 95, 99))
        self.assertEqual(result["error_rate"], 0.01)
        self.assertEqual(result["mean_ms"], 50.5)

    def test_invalid_and_empty_logs(self):
        rows = [{}, {"latency_ms": float("nan"), "ok": True},
                {"latency_ms": -1, "ok": False}, {"latency_ms": 1, "ok": "yes"}]
        result = analyze_logs(rows)
        self.assertEqual(result["invalid"], 4)
        self.assertIsNone(result["error_rate"])
        self.assertIsNone(analyze_logs([])["p99_ms"])

    def test_webhook_valid_tampered_and_wrong_secret(self):
        secret, body, timestamp = b"test-only-secret", b'{"x":1}', "1000"
        digest = hmac.new(secret, timestamp.encode() + b"." + body, hashlib.sha256).hexdigest()
        self.assertTrue(verify_webhook(secret, timestamp, body, digest, now=1000))
        self.assertFalse(verify_webhook(secret, timestamp, body + b" ", digest, now=1000))
        self.assertFalse(verify_webhook(b"wrong", timestamp, body, digest, now=1000))
        self.assertFalse(verify_webhook(secret, "1001", body, digest, now=1000))

    def test_webhook_freshness_and_malformed(self):
        secret, body, timestamp = b"test-only-secret", b"data", "1000"
        digest = hmac.new(secret, b"1000.data", hashlib.sha256).hexdigest()
        self.assertFalse(verify_webhook(secret, timestamp, body, digest, now=1301))
        self.assertFalse(verify_webhook(secret, timestamp, body, digest, now=699))
        self.assertFalse(verify_webhook(secret, "invalid", body, digest, now=1000))
        self.assertFalse(verify_webhook(secret, timestamp, body, "bad", now=1000))
        # Replay within the window is valid authentication; deduplication is separate.
        self.assertTrue(verify_webhook(secret, timestamp, body, digest, now=1100))


class RouterTests(unittest.TestCase):
    def test_filters_and_transient_fallback(self):
        specs = [ModelSpec("wrong-region", "us", frozenset({"tools"}), 100, 0),
                 ModelSpec("no-tools", "eu", frozenset(), 100, 0),
                 ModelSpec("primary", "eu", frozenset({"tools"}), 100, 1),
                 ModelSpec("backup", "eu", frozenset({"tools"}), 100, 2)]
        calls = []
        def generate(name, prompt):
            calls.append(name)
            if name == "primary":
                raise TimeoutError()
            return {"answer": "ok"}
        router = ModelRouter(specs, generate)
        result = router.route("hello", frozenset({"tools"}), {"eu"},
                              {s.name: 10 for s in specs}, 10,
                              lambda output: "answer" in output)
        self.assertEqual(result["model"], "backup")
        self.assertEqual(calls, ["primary", "backup"])

    def test_model_specific_budget(self):
        specs = [ModelSpec("a", "eu", frozenset(), 20, 1),
                 ModelSpec("b", "eu", frozenset(), 20, 2)]
        router = ModelRouter(specs, lambda name, prompt: name)
        result = router.route("x", frozenset(), {"eu"}, {"a": 19, "b": 10}, 5, bool)
        self.assertEqual(result["model"], "b")
        with self.assertRaises(ValueError):
            router.route("x", frozenset(), {"us"}, {"a": 1}, 1, bool)

    def test_validation_failure_does_not_fallback(self):
        specs = [ModelSpec("a", "eu", frozenset(), 20, 1),
                 ModelSpec("b", "eu", frozenset(), 20, 2)]
        calls = []
        def generate(name, prompt):
            calls.append(name)
            return "invalid"
        with self.assertRaises(ValueError):
            ModelRouter(specs, generate).route("x", frozenset(), {"eu"},
                                              {"a": 1, "b": 1}, 1, lambda _: False)
        self.assertEqual(calls, ["a"])

    def test_exhausted_attempt_budget(self):
        specs = [ModelSpec("a", "eu", frozenset(), 20, 1)]
        def generate(name, prompt):
            raise ConnectionError()
        with self.assertRaises(RuntimeError):
            ModelRouter(specs, generate).route("x", frozenset(), {"eu"}, {"a": 1}, 1, bool)


if __name__ == "__main__":
    unittest.main()
