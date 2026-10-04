# Interview Explanations and Answer Scripts

## How to sound deep without sounding rehearsed

A strong answer is not a pile of advanced words. It is a clear chain of reasoning:

1. Clarify the contract and constraints.
2. State a simple baseline.
3. Identify the bottleneck.
4. Choose a data structure or invariant that removes it.
5. Prove why the optimized approach is correct.
6. State time and space complexity.
7. Test normal and adversarial cases.
8. Discuss a production or follow-up trade-off.

Use this sentence pattern:

> I will first establish a correct baseline, then optimize the repeated work. The key invariant is ____. That gives us ____ complexity. I will validate it with empty input, the smallest valid input, duplicates, and a boundary case.

Do not claim a solution is optimal without stating the assumptions. For example, hashing is expected O(1), not a mathematical worst-case guarantee, and recursion may be unsafe for a very deep tree.

# Part I: Priority coding answer scripts

## 1. Two Sum

- Baseline: test every pair, O(n^2) time and O(1) extra space.
- Better: sort values with original indexes and use two pointers, O(n log n), but sorting changes the index relationship.
- Optimal: maintain a map from value to index. For each value `x`, look for `target - x` among values already seen.
- Invariant: before processing index `i`, the map contains exactly the values at earlier indexes.
- Complexity: expected O(n) time and O(n) space.
- Edge cases: duplicate values, negative targets, and no valid pair.
- Strong follow-up: if the input is sorted, use two pointers and O(1) extra space.

Interview line:

> I check before inserting the current value, so an element is never paired with itself. This also naturally handles duplicates because the earlier occurrence is already in the map.

## 2. Group Anagrams

- Baseline: compare every pair by character counts, O(n^2 * k).
- Better: sort each word and use the sorted word as a key, O(n*k log k).
- Optimal for a fixed alphabet: use a 26-count signature, O(n*k) time.
- Invariant: words are in the same group exactly when their signatures are equal.
- Complexity: O(n*k) with fixed alphabet; O(n*k) space for output and keys.
- Edge cases: empty strings, repeated words, mixed case, and Unicode assumptions.
- Follow-up: for Unicode, use a frequency map or normalized code-point representation.

## 3. Product of Array Except Self

- Baseline: multiply all other values for every index, O(n^2).
- Better: store prefix and suffix products, O(n) time and O(n) extra space.
- Optimal: store prefix products in the output and maintain one running suffix product, O(n) time and O(1) extra space excluding output.
- Invariant: after the first pass, `output[i]` equals the product strictly to the left; during the second pass it is multiplied by the product strictly to the right.
- Edge cases: one or more zeroes, negative values, and integer overflow.
- Follow-up: choose a wider numeric type or define overflow behavior explicitly.

## 4. Subarray Sum Equals K

- Baseline: enumerate every start and end, O(n^2).
- Better: prefix sums with repeated lookup, still O(n^2) without a map.
- Optimal: if current prefix is `P`, a previous prefix `P-k` forms a valid subarray. Count previous prefixes in a map.
- Invariant: the map stores how many times each prefix sum has appeared before the current index.
- Complexity: expected O(n) time and O(n) space.
- Edge cases: negative numbers, zero, repeated prefix sums, and the empty prefix.
- Critical detail: initialize frequency of prefix `0` to `1` so a valid subarray beginning at index zero is counted.

## 5. 3Sum

- Baseline: three nested loops, O(n^3).
- Better: fix one value and use a hash set for the remaining pair, O(n^2) expected time.
- Optimal standard approach: sort, fix `i`, and use two pointers, O(n^2) time and O(1) auxiliary space.
- Invariant: for fixed `i`, the left/right pointers search a sorted range; if the sum is too small, only moving left can increase it.
- Complexity: O(n^2) time after sorting.
- Edge cases: duplicate triplets, fewer than three values, all zeroes, and integer overflow.
- Strong line: duplicate skipping is part of correctness because the output is a set of value triplets, not index triplets.

## 6. Longest Substring Without Repeating Characters

- Baseline: generate substrings and test uniqueness, O(n^3).
- Better: sliding window with a set, O(n) amortized.
- Optimal: store the last index of each character and jump the left boundary, O(n).
- Invariant: the current window always contains unique characters.
- Critical detail: `left = max(left, last[ch] + 1)` prevents moving the boundary backward.
- Edge cases: empty string, repeated first character, and character-set assumptions.

## 7. Minimum Window Substring

- Baseline: enumerate windows and count characters, O(n^2 * alphabet).
- Better: sliding window with counts.
- Optimal: expand right until all required counts are satisfied, then shrink left while preserving validity.
- Invariant: when `missing == 0`, the current window covers the target multiset; the shrinking phase finds the smallest valid window ending at the current right index.
- Complexity: O(|s| + |t|) time and O(alphabet) space for a fixed character set.
- Edge cases: repeated target characters, target longer than source, empty target, and no solution.
- Follow-up: stream processing requires a different output contract because the final minimum may not be known until the end.

## 8. Sliding Window Maximum

- Baseline: scan each window, O(n*k).
- Better: heap with lazy removal, O(n log k).
- Optimal: decreasing deque of indexes, O(n) amortized.
- Invariant: deque indexes are inside the current window and their values decrease from front to back; the front is the maximum.
- Complexity: every index enters and leaves once, so O(n) time.
- Edge cases: `k=1`, `k=n`, duplicate values, and invalid `k`.

## 9. Merge Intervals

- Baseline: repeatedly compare and merge, potentially O(n^2).
- Optimal: sort by start and scan once, O(n log n).
- Invariant: `result.back()` represents the complete union of all processed intervals that overlaps the current interval if and only if the current start is no greater than its end.
- Edge cases: touching intervals, nested intervals, empty input, and malformed intervals.
- Clarify whether `[1,3]` and `[3,5]` should merge; most versions treat them as overlapping.

## 10. Meeting Rooms II

- Baseline: compare every interval against every active meeting.
- Better: sort starts and ends separately, O(n log n).
- Alternative: min heap of end times, O(n log n).
- Invariant for two arrays: if the next start is before the earliest end, a new room is needed; otherwise one room becomes free.
- Follow-up: if cancellations or live updates exist, use an event stream or indexed data structure.

## 11. Reverse Linked List

- Baseline: recursive reversal, O(n) time and O(n) call stack.
- Optimal iterative method: keep `previous`, `current`, and `next` before changing the pointer.
- Invariant: the list segment before `current` is already reversed and points backward through `previous`.
- Edge cases: empty list, one node, and a cycle, if cycles are not excluded.
- Strong line: saving `next` before rewiring is essential because otherwise the remaining list is lost.

## 12. Reorder List

- Baseline: repeatedly find the tail, O(n^2).
- Optimal: find midpoint with slow/fast pointers, reverse the second half, then weave the two lists, O(n) time and O(1) extra space.
- Invariant: after each weave, the prefix contains the required alternating order and both remaining halves are still correctly linked.
- Edge cases: one, two, odd, and even node counts.

## 13. Copy List with Random Pointer

- Baseline: map each original node to a clone, then assign pointers, O(n) time and O(n) space.
- Space-optimized approach: interleave each clone after its original, set random pointers using `original->random->next`, then separate the lists.
- Invariant: every original node is immediately followed by its clone during the middle phase.
- Edge cases: null random pointers, self-random pointers, and empty list.

## 14. Binary Tree Level Order Traversal

- DFS alternative: collect values by depth recursively.
- Optimal natural approach: BFS queue, processing exactly the current queue size as one level.
- Invariant: before a level loop, the queue contains precisely the nodes at that depth.
- Complexity: O(n) time and O(w) queue space, where `w` is maximum width.
- Follow-up: for a very deep tree, iterative traversal avoids call-stack overflow.

## 15. Binary Tree Right Side View

- BFS: record the last node in each level.
- DFS: traverse right before left and record the first node at each depth.
- Invariant for DFS: the first node visited at a depth is the visible node because right branches are prioritized.
- Edge cases: empty tree, skewed tree, and duplicate values. Use node position, not value identity.

## 16. Diameter of Binary Tree

- Baseline: compute height separately for every node, O(n^2) in a skewed tree.
- Optimal: one postorder traversal returns height and updates the best `leftHeight + rightHeight`.
- Invariant: when processing a node, child heights are already exact, so the longest path through that node is known.
- Clarify that the answer is usually measured in edges, not nodes.

## 17. Lowest Common Ancestor

- If parent pointers exist, store ancestors of one node and walk the other.
- Without parent pointers, recursively search both subtrees.
- Invariant: a non-null result means the subtree contains one target or the confirmed LCA of both.
- Edge cases: one target is ancestor of the other; clarify whether both nodes are guaranteed to exist.

## 18. Validate BST

- Baseline: inorder traversal and verify strict increase.
- Optimal explanation: recursively enforce an open numeric range `(lower, upper)`.
- Invariant: every node in a subtree must remain within the bounds imposed by all ancestors.
- Edge cases: duplicate values, `INT_MIN`, `INT_MAX`, and an empty tree.
- Use wider bounds or optional bounds to avoid integer-boundary overflow.

## 19. Kth Smallest in BST

- Baseline: collect all values and sort, O(n log n).
- Optimal: iterative inorder traversal; a BST inorder traversal is sorted.
- Invariant: every popped node is the next smallest unvisited value.
- Complexity: O(h+k) typical traversal work and O(h) stack space.
- Follow-up: for frequent queries, augment nodes with subtree sizes.

## 20. Serialize and Deserialize Binary Tree

- Design a bijective representation that preserves null children and ordering.
- Preorder with null markers is simple: serialize node, left, right; deserialize in the same sequence.
- Invariant: the decoder consumes exactly one token for each recursive subtree root, including null markers.
- Complexity: O(n) time and O(n) serialized size.
- Production concerns: version the format, limit input size, validate malformed tokens, and never deserialize untrusted objects directly.

## 21. Number of Islands

- Baseline: repeatedly scan or flood-fill without marking, which repeats work.
- Optimal: scan once and BFS/DFS each unvisited land cell, O(rows*cols).
- Invariant: after a flood fill, every cell in that island is marked and will never be processed again.
- Edge cases: empty grid, one row, diagonal cells, and whether mutation is allowed.
- Follow-up: for dynamic land additions, use Union Find.

## 22. Course Schedule

- Model each prerequisite as a directed edge.
- Cycle means no valid ordering.
- Kahn’s algorithm repeatedly removes zero-indegree nodes; if not all nodes are removed, a cycle exists.
- Invariant: the queue contains courses whose remaining prerequisites are all satisfied.
- Complexity: O(V+E).
- Follow-up: DFS coloring uses states unvisited, visiting, and complete.

## 23. Binary Search and Search on Answer

- Standard binary search requires a sorted or monotonic predicate.
- For capacity, Koko, or shipping problems, binary search the smallest feasible answer.
- Invariant: maintain a search interval containing the answer; discard only a region proven impossible.
- Edge cases: overflow in `left + right`, impossible bounds, and monotonicity assumptions.
- Strong line: the hard part is proving the feasibility predicate is monotonic before writing the loop.

## 24. Kth Largest Element

- Baseline: sort, O(n log n).
- Better: heap of size `k`, O(n log k).
- Average-optimal: Quickselect, expected O(n), worst-case O(n^2).
- Invariant for heap: it contains the largest `k` values seen, with the smallest of them at the top.
- Discuss deterministic worst-case requirements before choosing Quickselect.

## 25. Merge K Sorted Lists

- Pairwise merging can be O(N*k).
- Divide and conquer gives O(N log k).
- Min heap gives O(N log k) and naturally selects the next smallest head.
- Invariant: heap contains the smallest unmerged node from each non-empty list.
- Edge cases: empty lists, duplicate values, and pointer ownership.

## 26. House Robber

- Recurrence: `dp[i] = max(dp[i-1], dp[i-2] + value[i])`.
- Invariant: the rolling values represent the best result through the previous one and two positions.
- Complexity: O(n) time and O(1) space.
- Explain why taking adjacent houses is forbidden by the recurrence.
- Follow-up: circular houses require solving two linear ranges.

## 27. Coin Change

- Brute force recursively tries every combination and is exponential.
- Bottom-up DP computes the minimum coins for each amount from smaller amounts.
- Invariant: when computing `dp[a]`, every `dp[a-coin]` is already optimal.
- Complexity: O(amount * number_of_coins).
- Edge cases: amount zero, impossible amount, duplicate coins, and coin zero.

## 28. Word Break

- Baseline: recursive partitioning is exponential.
- DP: `dp[i]` means the prefix ending before `i` can be segmented.
- Invariant: `dp[i]` is true when there is a previous reachable boundary `j` and `s[j:i]` is a dictionary word.
- Complexity: O(n^2) substring checks before accounting for hashing/string-copy costs.
- Follow-up: Trie can reduce repeated prefix work for a large dictionary.

## 29. Longest Increasing Subsequence

- DP solution: O(n^2), where `dp[i]` is the best subsequence ending at `i`.
- Optimal tails method: keep the smallest possible ending value for each length and use lower_bound.
- Invariant: `tails[length-1]` is the smallest ending value known for an increasing subsequence of that length; it is not necessarily the actual subsequence.
- Complexity: O(n log n).
- Clarify strict versus non-decreasing subsequence.

## 30. Jump Game

- DP or recursive choices are unnecessary for reachability.
- Greedy keeps the farthest reachable index.
- Invariant: every index up to `farthest` is reachable; if current index exceeds it, the target is impossible.
- Complexity: O(n) time and O(1) space.
- Jump Game II changes the objective from reachability to minimum jumps and uses range expansion.

## 31. Subsets and Permutations

- Subsets: each element creates include/exclude branches, producing `2^n` results.
- Permutations: choose one unused position at each depth, producing `n!` results.
- Invariant: the current path is a valid partial answer; backtracking restores the exact prior state.
- Edge cases: duplicates require sorting and duplicate skipping for unique-output variants.
- State the output-size lower bound; no algorithm can emit all answers faster than the output itself.

## 32. Word Search

- DFS from each matching cell with four directions.
- Mark the current cell temporarily or use a visited set, then restore it on return.
- Invariant: the current path spells exactly the prefix being searched and contains no reused cell.
- Complexity: O(rows*cols*4^wordLength) worst case.
- Follow-up: a Trie supports searching many words in one board traversal.

## 33. Trie

- Hash set supports exact lookup but not efficient prefix traversal.
- A Trie uses one edge per character; insert/search/prefix are O(word length).
- Invariant: the node reached after consuming a string represents exactly that prefix.
- Discuss memory cost, alphabet assumptions, deletion, Unicode, and compressed/radix Trie alternatives.

## 34. LRU Cache

- Need O(1) lookup and O(1) recency updates.
- Hash map gives lookup; doubly linked list gives removal and move-to-front.
- Invariant: list order is most-recent to least-recent, and every map entry points to its exact list node.
- Discuss capacity zero, updating existing keys, thread safety, TTL, and metrics.

## 35. Time-Based Key-Value Store

- Store each key’s values ordered by timestamp.
- Use binary search for the greatest timestamp less than or equal to the query.
- Invariant: history remains sorted, so `upper_bound` identifies the first invalid future version.
- Discuss out-of-order writes: append is insufficient; use insertion, buffering, or an ordered map depending on constraints.

## 36. Union Find

- Parent pointers represent components.
- Path compression makes future finds shallow; union by rank/size avoids tall trees.
- Invariant: two nodes have the same root exactly when they belong to the same connected component.
- Complexity: near O(1) amortized, formally O(alpha(n)) per operation.
- Follow-up: rollback Union Find is needed for some offline dynamic-connectivity problems.

## 37. Topological Sort

- Applies only to a directed acyclic graph.
- Kahn’s algorithm uses indegrees; DFS uses a temporary visiting state to detect cycles.
- Invariant: removing a zero-indegree node preserves all valid precedence constraints.
- Edge cases: disconnected graph, duplicate edges, and cycles.

## 38. Rate Limiter

- Fixed window is simple but allows boundary bursts.
- Sliding window is more accurate but costs more state.
- Token bucket allows bursts up to capacity while controlling average rate.
- Leaky bucket smooths output.
- Production concerns: monotonic time, distributed state, atomic updates, clock skew, fail-open versus fail-closed, and tenant fairness.

## 39. Retry and Idempotency

- Retry only transient failures, not validation or permission errors.
- Use exponential backoff with jitter to avoid synchronized retry storms.
- An idempotency key lets the server return the same result instead of creating duplicate side effects.
- Bound attempts, add deadlines, classify errors, and send exhausted jobs to a dead-letter path.
- Explain that retries without idempotency can make an outage worse.

## 40. RAG quality debugging

Separate retrieval from generation:

1. Verify the query and tenant permissions.
2. Inspect chunking, metadata, embedding version, and index freshness.
3. Measure retrieval recall and ranking quality on a golden set.
4. Check whether the correct evidence reached the prompt.
5. Check prompt instructions, context truncation, and model version.
6. Validate citations and answer groundedness.
7. Compare latency and token cost by stage.

Strong diagnosis:

> I would not immediately change the prompt. First I would determine whether the system failed to retrieve the evidence or retrieved it but generated an unsupported answer. Those are different faults with different fixes.

# Part II: Deep system-design answer framework

## Opening

> I will clarify the primary user and success metric first. Then I will estimate scale, define the API and data model, draw the main read/write path, and finally cover reliability, privacy, observability, and cost.

## RAG assistant answer

- Ingestion: connector, parser, cleaner, chunker, metadata extractor.
- Access control: preserve source permissions in document metadata and filter before generation.
- Indexing: embedding service, vector index, keyword index, reranker.
- Query: authenticate, classify, retrieve, rerank, build bounded context, generate, validate citations.
- Reliability: timeouts, provider fallback, queue-based ingestion, retry and dead-letter paths.
- Quality: retrieval recall, MRR, groundedness, citation correctness, answer rating.
- Safety: prompt-injection detection, untrusted-document boundaries, tool permissions, PII handling.
- Cost: cache embeddings and repeated queries, batch ingestion, route simple queries to cheaper models.

Depth sentence:

> The security boundary must be enforced during retrieval, not merely described in the prompt, because the model is not an authorization system.

## LLM gateway answer

- Gateway authenticates tenants and applies quotas.
- Router chooses a provider/model based on capability, latency, availability, and cost.
- Request state carries timeout, budget, trace ID, and idempotency information.
- Stream results where useful, but enforce output limits and cancellation.
- Record metadata, not sensitive raw prompts by default.
- Use circuit breakers and fallback policies with quality guardrails.

Depth sentence:

> A fallback is not automatically safe: changing the model can change tool behavior, output schema, latency, and privacy properties, so fallback policies need evaluation and observability.

## Evaluation platform answer

- Version prompts, models, retrieval configuration, and datasets together.
- Run deterministic checks for schema, citations, and policy violations.
- Run model-based or human evaluation with calibrated rubrics.
- Slice results by language, customer, document type, difficulty, and failure mode.
- Compare against a baseline and block regressions on quality, safety, latency, and cost.

Depth sentence:

> A single average score can hide a severe regression for a small but important customer segment, so evaluation must be slice-aware.

# Part III: AI and ML answer scripts

## Precision versus recall

- Precision asks: of retrieved or predicted positives, how many were correct?
- Recall asks: of all relevant items, how many were found?
- Search and retrieval often trade recall for precision through candidate generation and reranking.
- The correct threshold depends on the cost of false positives and false negatives.

## Offline versus online evaluation

- Offline tests are repeatable and useful for regression detection.
- Online metrics measure real user value but can be noisy and affected by distribution shift.
- Use guardrails for latency, error rate, safety, cost, and user complaints.
- Do not optimize a proxy metric that is disconnected from the user outcome.

## Model-quality regression

Check data distribution, feature pipeline, model version, threshold, calibration, label delay, and slice-specific behavior. Compare a known-good baseline, reproduce on a fixed dataset, and roll back or disable the feature if user harm is possible.

# Part IV: FDE answer scripts

## Ambiguous customer request

> I would separate the requested feature from the underlying business outcome. I would identify the user, current workflow, decision being improved, data available, permissions, and measurable success criterion. Then I would propose a small safe pilot with explicit exclusions, evaluation, owner, and rollback plan.

## Customer asks for unsafe access

> I would explain the constraint in terms of the customer’s risk, propose a permission-preserving alternative, document the decision, and escalate if the requirement conflicts with policy. Speed is important, but bypassing an authorization boundary creates a larger production and trust failure.

## Two-week proof of concept

- Day 1-2: discovery, data access, success metrics, risk review.
- Day 3-5: thin vertical slice with real data and logging.
- Day 6-8: evaluation set, error analysis, permissions, and failure handling.
- Day 9-11: pilot with selected users and feedback.
- Day 12-14: results, limitations, production-readiness gaps, and next plan.

## Production incident

1. Establish impact and affected scope.
2. Stabilize: rollback, disable, rate-limit, or fail over.
3. Preserve evidence and assign owners.
4. Form hypotheses and add targeted instrumentation.
5. Fix the immediate failure.
6. Validate recovery and communicate status.
7. Complete a blameless postmortem with prevention work.

# Part V: Behavioral answer quality

Avoid saying only “we” when explaining your contribution. State the decision you made, the trade-off, and the measurable result.

Strong structure:

- Situation: concise context.
- Task: your responsibility.
- Action: specific technical and interpersonal choices.
- Result: measurable outcome.
- Reflection: what you changed afterward.

A strong failure answer includes an actual mistake, the impact, the detection gap, the corrective action, and the process or technical change that prevents repetition.

# Final interview phrases worth practicing

- “The key assumption I need to confirm is..."
- “The simplest correct baseline is..."
- “The repeated work is..., so I will cache/aggregate/index..."
- “The invariant during this loop is..."
- “This is expected O(1) because..., but the worst case is..."
- “I would separate retrieval failure from generation failure by measuring..."
- “The authorization decision belongs before retrieval/tool execution, not inside the prompt."
- “I would make this operation idempotent because retries are unavoidable."
- “I would roll this out gradually behind a flag and compare it with a baseline."
- “The trade-off I am making is..., because the current requirement prioritizes..."
