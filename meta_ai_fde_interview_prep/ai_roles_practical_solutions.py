"""Twenty interview reference solutions. Python 3.10+, standard library only.

See ai_roles_coding_walkthroughs.md for contracts and production limitations.
In-memory components are single-process; only explicitly locked operations are
thread-safe. This module makes no network calls and requires no credentials.
"""
from __future__ import annotations

import asyncio
import hashlib
import heapq
import hmac
import json
import math
import random
import re
import sqlite3
import threading
import time
from collections import Counter, OrderedDict, deque
from dataclasses import dataclass
from typing import Callable, Iterable


# 1. LRU cache: OrderedDict combines a hash table and recency ordering.
class LRUCache:
    def __init__(self, capacity: int):
        if capacity <= 0:
            raise ValueError("capacity must be positive")
        self.capacity = capacity
        self.data = OrderedDict()
        self.lock = threading.Lock()

    def get(self, key):
        with self.lock:
            value = self.data[key]  # A miss raises KeyError; None is a valid value.
            self.data.move_to_end(key)
            return value

    def put(self, key, value):
        with self.lock:
            self.data[key] = value
            self.data.move_to_end(key)
            if len(self.data) > self.capacity:
                self.data.popitem(last=False)


# 2. TTL cache: bounded storage, monotonic expiry, lazy stale-entry cleanup.
class TTLCache:
    def __init__(self, capacity: int, clock=time.monotonic):
        if capacity <= 0:
            raise ValueError("capacity must be positive")
        self.capacity, self.clock = capacity, clock
        self.data = OrderedDict()
        self.lock = threading.Lock()

    def get(self, key):
        with self.lock:
            value, expires = self.data[key]
            if self.clock() >= expires:
                del self.data[key]
                raise KeyError(key)
            self.data.move_to_end(key)
            return value

    def put(self, key, value, ttl: float):
        if not math.isfinite(ttl) or ttl <= 0:
            raise ValueError("ttl must be positive and finite")
        with self.lock:
            now = self.clock()
            for stale in [k for k, (_, expiry) in self.data.items() if expiry <= now]:
                del self.data[stale]
            self.data[key] = (value, now + ttl)
            self.data.move_to_end(key)
            if len(self.data) > self.capacity:
                self.data.popitem(last=False)


# 3. Token bucket: one instance per rate-limit scope.
class TokenBucket:
    def __init__(self, capacity: float, rate: float, clock=time.monotonic):
        if not all(math.isfinite(x) and x > 0 for x in (capacity, rate)):
            raise ValueError("capacity and rate must be positive and finite")
        self.capacity, self.rate, self.clock = capacity, rate, clock
        self.tokens, self.last = capacity, clock()
        self.lock = threading.Lock()

    def allow(self, cost=1.0) -> bool:
        if not math.isfinite(cost) or not 0 < cost <= self.capacity:
            raise ValueError("cost must be in (0, capacity]")
        with self.lock:
            now = self.clock()
            self.tokens = min(self.capacity, self.tokens + (now - self.last) * self.rate)
            self.last = now
            if self.tokens < cost:
                return False
            self.tokens -= cost
            return True


# 4. Exact sliding window: accepted requests in (now-window, now].
class SlidingWindowLimiter:
    def __init__(self, limit: int, window: float, clock=time.monotonic):
        if limit <= 0 or not math.isfinite(window) or window <= 0:
            raise ValueError("positive limit and finite positive window required")
        self.limit, self.window, self.clock = limit, window, clock
        self.events = deque()
        self.lock = threading.Lock()

    def allow(self) -> bool:
        with self.lock:
            now = self.clock()
            while self.events and self.events[0] <= now - self.window:
                self.events.popleft()
            if len(self.events) >= self.limit:
                return False
            self.events.append(now)
            return True


# 5. Durable idempotency for a local database mutation, NOT an external API.
class EventProcessor:
    def __init__(self, path: str):
        self.db = sqlite3.connect(path, timeout=5, isolation_level=None)
        self.db.executescript("""
            CREATE TABLE IF NOT EXISTS events (
                tenant TEXT NOT NULL, event_id TEXT NOT NULL,
                payload_hash TEXT NOT NULL, response TEXT NOT NULL,
                PRIMARY KEY (tenant, event_id)
            );
            CREATE TABLE IF NOT EXISTS records (
                id INTEGER PRIMARY KEY, tenant TEXT NOT NULL,
                name TEXT NOT NULL
            );
        """)

    def process(self, tenant: str, event_id: str, payload: dict) -> dict:
        if not tenant or not event_id or set(payload) != {"name"}:
            raise ValueError("tenant, event ID, and exactly one name field required")
        if not isinstance(payload["name"], str) or not payload["name"].strip():
            raise ValueError("name must be nonempty text")
        canonical = json.dumps(payload, sort_keys=True, separators=(",", ":"),
                               ensure_ascii=False, allow_nan=False)
        digest = hashlib.sha256(canonical.encode()).hexdigest()
        self.db.execute("BEGIN IMMEDIATE")
        try:
            row = self.db.execute(
                "SELECT payload_hash, response FROM events WHERE tenant=? AND event_id=?",
                (tenant, event_id)).fetchone()
            if row:
                if row[0] != digest:
                    raise ValueError("idempotency key reused with different payload")
                result = json.loads(row[1])
            else:
                cur = self.db.execute("INSERT INTO records(tenant, name) VALUES (?, ?)",
                                      (tenant, payload["name"]))
                result = {"record_id": cur.lastrowid}
                self.db.execute("INSERT INTO events VALUES (?, ?, ?, ?)",
                                (tenant, event_id, digest, json.dumps(result)))
            self.db.execute("COMMIT")
            return result
        except BaseException:
            if self.db.in_transaction:
                self.db.execute("ROLLBACK")
            raise

    def close(self):
        self.db.close()


# 6. Bounded pending queue; output retention is still O(number of inputs).
async def run_bounded(items: Iterable, worker: Callable, workers=4, max_pending=8):
    """worker is async; returns ordered (success: bool, value_or_exception) pairs.

    Worker exceptions are collected, not retried. Cancellation propagates.
    The input iterator must be finite and must not block the event loop.
    """
    if workers <= 0 or max_pending <= 0:
        raise ValueError("workers and max_pending must be positive")
    queue = asyncio.Queue(maxsize=max_pending)
    stop = object()
    results = {}

    async def consume():
        while True:
            job = await queue.get()
            try:
                if job is stop:
                    return
                index, item = job
                try:
                    results[index] = (True, await worker(item))
                except Exception as exc:
                    results[index] = (False, exc)
            finally:
                queue.task_done()

    tasks = [asyncio.create_task(consume()) for _ in range(workers)]
    try:
        for index, item in enumerate(items):
            await queue.put((index, item))
        for _ in tasks:
            await queue.put(stop)
        await asyncio.gather(*tasks)
        return [results[i] for i in range(len(results))]
    finally:
        for task in tasks:
            if not task.done():
                task.cancel()
        await asyncio.gather(*tasks, return_exceptions=True)


# 7. Bounded retry with full jitter. Operation must be safe to retry.
def retry(operation, attempts=3, base=0.1, cap=2.0,
          retry_on=(TimeoutError,), sleep=time.sleep, rng=random.random):
    if attempts < 1 or not all(math.isfinite(x) and x >= 0 for x in (base, cap)):
        raise ValueError("positive attempts and finite nonnegative delays required")
    delay = min(base, cap)
    for attempt in range(attempts):
        try:
            return operation()
        except retry_on:
            if attempt == attempts - 1:
                raise
            sleep(rng() * delay)
            delay = min(cap, delay * 2)


# 8. Sequential circuit breaker. Protect separately if used concurrently.
class CircuitOpen(RuntimeError):
    pass


class CircuitBreaker:
    def __init__(self, threshold=3, cooldown=5.0, clock=time.monotonic,
                 failure_types=(TimeoutError, ConnectionError)):
        if threshold <= 0 or not math.isfinite(cooldown) or cooldown <= 0:
            raise ValueError("positive threshold and finite positive cooldown required")
        self.threshold, self.cooldown, self.clock = threshold, cooldown, clock
        self.failure_types = failure_types
        self.failures, self.opened_at = 0, None

    def call(self, operation):
        if self.opened_at is not None:
            if self.clock() - self.opened_at < self.cooldown:
                raise CircuitOpen("dependency cooling down")
            # In this sequential API, the next call is the half-open probe.
        try:
            result = operation()
        except self.failure_types:
            self.failures += 1
            if self.failures >= self.threshold:
                self.opened_at = self.clock()
            raise
        except Exception:
            # A business/validation error is not a dependency-health failure.
            self.failures, self.opened_at = 0, None
            raise
        self.failures, self.opened_at = 0, None
        return result


# 9. Trie with deterministic lexicographic completion.
class Trie:
    END = None

    def __init__(self):
        self.root = {}

    def insert(self, word: str):
        node = self.root
        for char in word:
            node = node.setdefault(char, {})
        node[self.END] = True

    def autocomplete(self, prefix: str, k=5) -> list[str]:
        if k < 0:
            raise ValueError("k must be nonnegative")
        node = self.root
        for char in prefix:
            if char not in node:
                return []
            node = node[char]
        found, stack = [], [(prefix, node)]
        while stack and len(found) < k:
            word, current = stack.pop()
            if self.END in current:
                found.append(word)
            for char in sorted((c for c in current if c is not self.END), reverse=True):
                stack.append((word + char, current[char]))
        return found


# 10. Exact stream frequencies with heap-based top-k queries.
class TopKCounter:
    def __init__(self):
        self.counts = Counter()

    def add(self, item: str):
        self.counts[item] += 1

    def top(self, k: int):
        if k < 0:
            raise ValueError("k must be nonnegative")
        return heapq.nsmallest(k, self.counts.items(), key=lambda p: (-p[1], p[0]))


# 11. Inputs are finite iterables sorted by timestamp, values are (time, payload).
def merge_events(streams: Iterable[Iterable[tuple]]):
    heap = []

    def advance(source, iterator, previous=None):
        item = next(iterator, None)
        if item is None:
            return
        timestamp, payload = item
        if not math.isfinite(timestamp):
            raise ValueError("finite timestamps required")
        if previous is not None and timestamp < previous:
            raise ValueError("each source must be sorted")
        heapq.heappush(heap, (timestamp, source, payload, iterator))

    for source, stream in enumerate(streams):
        advance(source, iter(stream))
    while heap:
        timestamp, source, payload, iterator = heapq.heappop(heap)
        yield timestamp, payload
        advance(source, iterator, timestamp)


# 12. Sentence-aware greedy packing. Inject the real model's token counter.
def chunk_document(text: str, max_tokens: int,
                   count_tokens: Callable[[str], int]) -> list[str]:
    if max_tokens <= 0:
        raise ValueError("positive token budget required")
    chunks, current = [], ""
    sentences = re.split(r"(?<=[.!?])\s+|\n+", text.strip())
    for sentence in filter(None, sentences):
        if count_tokens(sentence) <= max_tokens:
            units = [sentence]
        else:
            # Long-sentence fallback preserves words, but not original whitespace.
            units = sentence.split()
        for unit in units:
            if count_tokens(unit) > max_tokens:
                raise ValueError("one word exceeds budget; use tokenizer-level splitting")
            candidate = f"{current} {unit}".strip()
            if count_tokens(candidate) <= max_tokens:
                current = candidate
            else:
                if current:
                    chunks.append(current)
                current = unit
    if current:
        chunks.append(current)
    return chunks


# 13. Trusted-boundary lexical baseline; authentication occurs upstream.
@dataclass(frozen=True)
class Principal:
    tenant: str
    user: str


@dataclass(frozen=True)
class Document:
    id: str
    tenant: str
    readers: frozenset[str]
    text: str


def retrieve(principal: Principal, query: str, documents: Iterable[Document],
             k=3, authorize=None) -> list[Document]:
    if k < 0:
        raise ValueError("k must be nonnegative")
    terms = set(re.findall(r"\w+", query.lower()))
    candidates = []
    seen = set()
    for doc in documents:
        if doc.tenant != principal.tenant or principal.user not in doc.readers:
            continue
        if authorize is not None and not authorize(principal, doc):
            continue  # Current authoritative access check; errors propagate closed.
        key = (doc.tenant, doc.id)
        if key in seen:
            raise ValueError("duplicate document ID in retrieval snapshot")
        seen.add(key)
        score = len(terms & set(re.findall(r"\w+", doc.text.lower())))
        if score:
            candidates.append((score, doc))
    candidates.sort(key=lambda pair: (-pair[0], pair[1].id))
    return [doc for _, doc in candidates[:k]]


# 14. Metrics for one query. Macro-average across queries outside this function.
def retrieval_metrics(ranked: list[str], relevance: dict[str, float], k: int):
    if k <= 0 or any(not math.isfinite(v) or v < 0 for v in relevance.values()):
        raise ValueError("positive k and finite nonnegative relevance required")
    if len(ranked) != len(set(ranked)):
        raise ValueError("deduplicate ranked document IDs before evaluating")
    selected = ranked[:k]
    relevant = {doc for doc, grade in relevance.items() if grade > 0}
    hits = [i for i, doc in enumerate(selected, 1) if doc in relevant]
    # Linear graded gain, rather than exponential gain; state the convention.
    dcg = sum(relevance.get(doc, 0) / math.log2(i + 1)
              for i, doc in enumerate(selected, 1))
    ideal = sum(grade / math.log2(i + 1) for i, grade in enumerate(
        sorted(relevance.values(), reverse=True)[:k], 1))
    return {"precision": len(hits) / k,
            "recall": len(hits) / len(relevant) if relevant else 0.0,
            "mrr": 1 / hits[0] if hits else 0.0,
            "ndcg": dcg / ideal if ideal else 0.0}


# 15. Immutable prompt versions and an explicit activation pointer.
@dataclass(frozen=True)
class PromptVersion:
    name: str
    version: str
    template: str
    sha256: str


class PromptRegistry:
    def __init__(self):
        self.versions, self.active = {}, {}

    def register(self, name: str, version: str, template: str) -> PromptVersion:
        if not name or not version or not template:
            raise ValueError("name, version, and template required")
        key = (name, version)
        item = PromptVersion(name, version, template,
                             hashlib.sha256(template.encode()).hexdigest())
        if key in self.versions and self.versions[key] != item:
            raise ValueError("registered versions are immutable")
        self.versions[key] = item
        return item

    def activate(self, name: str, version: str):
        self.versions[(name, version)]  # Fail before changing the active pointer.
        self.active[name] = version

    def get(self, name: str, version=None) -> PromptVersion:
        return self.versions[(name, version if version is not None else self.active[name])]


# 16. Caller groups tool calls with their results and supplies request token cost.
def truncate_conversation(system: list[dict], history_groups: list[list[dict]],
                          current: list[dict], budget: int, reserve: int,
                          count_request: Callable[[list[dict]], int]):
    if budget <= 0 or reserve < 0 or reserve > budget or not current:
        raise ValueError("invalid budget or empty current request")
    mandatory = system + current
    if count_request(mandatory) + reserve > budget:
        raise ValueError("protected instructions/current request exceed budget")
    chosen = []
    for group in reversed(history_groups):
        candidate = group + chosen
        if count_request(system + candidate + current) + reserve > budget:
            break  # Preserve a contiguous suffix; do not create unexplained gaps.
        chosen = candidate
    return system + chosen + current


# 17. Point-in-time event/availability semantics for one numerical feature.
@dataclass(frozen=True)
class FeatureValue:
    event_time: float
    available_at: float
    value: float


class FeatureStore:
    def __init__(self):
        self.rows = {}

    def put(self, tenant: str, entity: str, name: str, event_time: float,
            available_at: float, value: float):
        if not all((tenant, entity, name)) or not all(
                math.isfinite(v) for v in (event_time, available_at, value)):
            raise ValueError("IDs and finite numerical fields required")
        if available_at < event_time:
            raise ValueError("observed-feature availability precedes event")
        row = FeatureValue(event_time, available_at, value)
        records = self.rows.setdefault((tenant, entity, name), [])
        for old in records:
            if (old.event_time, old.available_at) == (event_time, available_at):
                if old != row:
                    raise ValueError("conflicting feature version")
                return
        records.append(row)

    def get(self, tenant: str, entity: str, name: str, as_of: float,
            max_age: float | None = None) -> FeatureValue:
        if not math.isfinite(as_of) or (max_age is not None and
                (not math.isfinite(max_age) or max_age < 0)):
            raise ValueError("finite as_of and nonnegative finite max_age required")
        candidates = [row for row in self.rows.get((tenant, entity, name), [])
                      if row.event_time <= as_of and row.available_at <= as_of]
        if not candidates:
            raise KeyError("no point-in-time feature")
        row = max(candidates, key=lambda r: (r.event_time, r.available_at))
        if max_age is not None and as_of - row.event_time > max_age:
            raise KeyError("feature is stale")
        return row


# 18. One record per completed attempt; ok represents success under your SLO.
def analyze_logs(rows: Iterable[dict]):
    durations, errors, invalid = [], 0, 0
    for row in rows:
        try:
            duration, ok = row["latency_ms"], row["ok"]
            if isinstance(duration, bool) or not isinstance(duration, (float, int)):
                raise ValueError()
            if not math.isfinite(duration) or duration < 0 or not isinstance(ok, bool):
                raise ValueError()
        except (KeyError, TypeError, ValueError):
            invalid += 1
            continue
        durations.append(duration)
        errors += not ok
    durations.sort()
    n = len(durations)

    def percentile(p):
        return durations[math.ceil(p * n) - 1] if n else None

    return {"count": n, "invalid": invalid,
            "error_rate": errors / n if n else None,
            "mean_ms": sum(durations) / n if n else None,
            "p50_ms": percentile(0.50), "p95_ms": percentile(0.95),
            "p99_ms": percentile(0.99)}


# 19. Explicit example protocol: HMAC-SHA256(secret, timestamp + '.' + raw_body).
def verify_webhook(secret: bytes, timestamp: str, body: bytes, signature: str,
                   now: float | None = None, tolerance=300.0) -> bool:
    """Authenticates bytes and freshness only; caller must deduplicate event IDs."""
    if not secret or not math.isfinite(tolerance) or tolerance < 0:
        raise ValueError("nonempty secret and finite nonnegative tolerance required")
    if not isinstance(timestamp, str) or not re.fullmatch(r"[0-9]{1,12}", timestamp):
        return False
    if not isinstance(signature, str) or not re.fullmatch(r"[0-9a-fA-F]{64}", signature):
        return False
    now = time.time() if now is None else now
    if not math.isfinite(now) or abs(now - int(timestamp)) > tolerance:
        return False
    message = timestamp.encode("ascii") + b"." + body
    expected = hmac.new(secret, message, hashlib.sha256).hexdigest()
    return hmac.compare_digest(expected, signature.lower())


# 20. Qualified model selection with bounded fallback on transient failures.
@dataclass(frozen=True)
class ModelSpec:
    name: str
    region: str
    capabilities: frozenset[str]
    context_limit: int
    priority: int


class ModelRouter:
    def __init__(self, specs: list[ModelSpec], generate: Callable):
        if len({s.name for s in specs}) != len(specs) or any(
                s.context_limit <= 0 for s in specs):
            raise ValueError("unique model names and positive context limits required")
        self.specs, self.generate = specs, generate

    def route(self, prompt: str, required: frozenset[str], allowed_regions: set[str],
              input_tokens: dict[str, int], reserve: int, validate: Callable,
              max_attempts=2):
        # Counts are per model because tokenizers may differ.
        if reserve < 0 or max_attempts <= 0:
            raise ValueError("nonnegative reserve and positive attempts required")
        eligible = sorted((s for s in self.specs
                           if s.region in allowed_regions
                           and required <= s.capabilities
                           and s.name in input_tokens
                           and 0 <= input_tokens[s.name]
                           and input_tokens[s.name] + reserve <= s.context_limit),
                          key=lambda s: (s.priority, s.name))
        if not eligible:
            raise ValueError("no qualified model")
        attempted = []
        last_error = None
        for spec in eligible[:max_attempts]:
            attempted.append(spec.name)
            try:
                output = self.generate(spec.name, prompt)
            except (TimeoutError, ConnectionError) as exc:
                last_error = exc
                continue
            if not validate(output):
                # Schema/policy errors do not silently trigger model shopping.
                raise ValueError("output failed validation")
            return {"model": spec.name, "output": output, "attempted": attempted}
        raise RuntimeError("qualified model attempts exhausted") from last_error


def demo():
    cache = LRUCache(2)
    cache.put("policy", "version 1")
    print("LRU:", cache.get("policy"))
    docs = [Document("d1", "acme", frozenset({"alice"}), "Password reset policy"),
            Document("d2", "other", frozenset({"alice"}), "Private password data")]
    found = retrieve(Principal("acme", "alice"), "password", docs)
    print("Authorized document IDs:", [d.id for d in found])
    print("Retrieval metrics:", retrieval_metrics(["d1"], {"d1": 1}, 1))
    print("Chunks:", chunk_document("Reset your password. Contact support for help.",
                                    4, lambda text: len(text.split())))
    registry = PromptRegistry()
    registry.register("support", "v1", "Answer using the supplied evidence.")
    registry.activate("support", "v1")
    print("Prompt version:", registry.get("support").version)


if __name__ == "__main__":
    demo()
