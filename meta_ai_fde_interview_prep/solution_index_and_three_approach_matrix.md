# Complete Solution Index and Three-Approach Matrix

## Honest coverage statement

The attached curriculum contains several hundred exercises. A useful preparation system should not pretend that every link already has a tested implementation. This file provides the solution route for the complete bank, while the C++ workbooks contain executable implementations for the highest-priority core.

For any problem, use the three levels below:

- **Brute:** simplest correct method and why it may time out.
- **Better:** remove a major repeated computation.
- **Optimal:** best method under stated constraints, with invariant, proof, complexity, and edge cases.

Detailed implementation sources:

- [top_50_coding_solutions.cpp](top_50_coding_solutions.cpp)
- [microsoft_full_master_question_bank.cpp](../microsoft_full_master_question_bank.cpp)
- [interview_explanations_and_answer_scripts.md](interview_explanations_and_answer_scripts.md)
- [personal_guidance_12_week_plan.md](personal_guidance_12_week_plan.md)

# 1. Mathematics and basic programming

| Problem family | Brute | Better | Optimal / interview explanation |
|---|---|---|---|
| Prime test | Try divisors to n | Try divisors to n/2 | Try divisors to sqrt(n); for many queries use a sieve |
| GCD / LCM | Enumerate common divisors | Repeated subtraction | Euclidean remainder algorithm; use 64-bit arithmetic for LCM |
| Count digits / reverse number | Convert to string | Repeated division | Repeated division with overflow checks |
| Armstrong number | String powers | Recompute powers | Digit extraction with precomputed powers |
| Divisors | Check every number | Stop at sqrt | Add paired divisors at sqrt; avoid duplicate square |
| Count primes | Test every number | Cache primality | Sieve of Eratosthenes for a range |
| Fast power | Multiply n times | Repeated squaring recursively | Binary exponentiation, O(log n) |
| Multiply strings | Convert to built-in integer | Grade-school multiplication with strings | Digit-array multiplication with carry |
| Modular exponentiation | Full integer power | Repeated squaring | Apply modulo at every multiplication and use wide intermediate type |

**Answer detail:** Always ask about input bounds, negative values, zero, overflow, and whether there are one or many queries.

# 2. Searching and sorting

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| First and last position | Linear scan | Find one occurrence then expand | Two binary searches for lower and upper bound, O(log n) |
| Search insert position | Linear scan | Sort then scan | Lower bound binary search |
| Rotated sorted array | Linear scan | Find pivot then binary search | Determine which half is sorted at each step |
| Rotated array with duplicates | Linear scan | Pivot preprocessing | When ends equal, shrink safely; worst case can be O(n) |
| Find minimum rotated array | Linear scan | Find pivot | Compare midpoint with right boundary |
| Peak element | Linear scan | Compare neighbors | If `nums[mid] < nums[mid+1]`, a peak exists right; otherwise left |
| Kth smallest sorted matrix | Flatten and sort | Heap of rows | Binary search value with count of elements <= value |
| Inversion count | Compare every pair | Merge-sort counting | Count cross inversions during merge, O(n log n) |
| Next permutation | Generate permutations | Find next by search | Find rightmost ascent, swap successor, reverse suffix |
| Allocate pages / aggressive cows | Try every answer | Greedy feasibility | Binary search the answer because feasibility is monotonic |
| Kth pair distance | Generate all distances | Sort distances | Binary search distance and count pairs <= distance |
| Count smaller after self | Compare later values | Fenwick after coordinate compression | Merge-sort counting or Fenwick tree |

**Proof template:** Define the monotonic predicate. Show that every answer below the lower boundary is impossible and every answer above the upper boundary is feasible or vice versa.

# 3. Arrays and hashing

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| Two Sum | All pairs, O(n^2) | Sort plus two pointers | Hash map of prior values, expected O(n) |
| Missing number | Search each value | Sort | XOR or arithmetic sum, O(n), O(1) extra |
| Find duplicates | Compare pairs | Frequency map | In-place sign marking if values are 1..n |
| Majority element | Count each value | Frequency map | Boyer-Moore cancellation |
| Majority element II | Frequency map | Sort and count | Generalized Boyer-Moore with at most two candidates |
| Maximum subarray | All subarrays | Prefix sums | Kadane: best subarray ending here |
| Circular maximum subarray | Enumerate circular ranges | Prefix/suffix | Max(Kadane, total - minimum subarray), handle all-negative |
| Maximum product subarray | Enumerate | DP arrays | Track max and min ending here because negative swaps them |
| Product except self | Recompute product | Prefix and suffix arrays | Prefix in output plus running suffix |
| Rotate array | Repeated one-step shifts | Extra array | Reverse whole array, then reverse sections |
| Move zeroes | Build a new array | Two scans | Stable compaction with write pointer |
| Sort colors | Counting | Sort | Dutch national flag with low/mid/high invariant |
| Subarray sum K | Enumerate subarrays | Prefix sums | Prefix-frequency map; initialize frequency of zero |
| Longest zero-sum subarray | Enumerate | Prefix sums | First index of each prefix sum |
| Longest consecutive sequence | Sort | Set | Start only at values without predecessor |
| Find duplicate number | Frequency set | Binary search value counts | Floyd cycle detection when constraints allow mutation model |
| Max chunks to make sorted | Enumerate cuts | Prefix max/suffix min | Track max prefix and compare with next minimum |
| Equilibrium index | Recompute left/right | Prefix arrays | Total sum and running left sum |
| Sum of all subarrays | Enumerate | Prefix sums | Contribution of value at i: `(i+1)*(n-i)*value` |
| Search 2D matrix | Scan all cells | Row binary search | Staircase walk or binary search under sorted-row/column assumptions |

# 4. Strings, two pointers, and windows

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| Valid palindrome | Reverse and compare | Two pointers skipping non-alphanumeric | Compare normalized ends in one pass |
| Valid anagram | Sort strings | Frequency map | Fixed-size frequency array when alphabet is known |
| Isomorphic strings | Compare all mappings | Two maps | Maintain bijection in one pass |
| Longest unique substring | Test every substring | Set window | Last-position map jumps left boundary |
| Find anagrams | Sort each window | Frequency compare | Fixed-size sliding frequency window |
| Permutation in string | Generate permutations | Sort windows | Sliding frequency difference |
| Longest replacement | Test every substring | Frequency window | Window length minus max frequency <= k |
| Minimum window | All substrings | Count-based windows | Expand until valid, shrink while valid |
| Longest palindrome | Expand for each center | DP table | Center expansion is O(n^2) and low memory; Manacher is O(n) if required |
| Palindromic substrings | Check every substring | DP | Center expansion counts each center |
| Reverse words | Split and rebuild | Trim and scan | Two pointers or tokenization with explicit whitespace contract |
| Atoi | Library conversion | Manual parse | Skip spaces, sign, digits, and clamp overflow |
| Decode string | Repeated replacement | Stack of strings | Stack counts and partial strings |
| Basic calculator | Repeated evaluation | Operator stack | One-pass stack with precedence and parentheses |
| Longest common prefix | Compare each pair | Sort lexicographically | Compare first and last sorted words |
| String multiplication | Built-in conversion | Grade-school strings | Digit array with carry |
| Word break | Recursive partitions | Memoization | DP over reachable word boundaries; Trie for large dictionary |
| Word ladder | Try all transformations repeatedly | BFS with wildcard buckets | BFS gives shortest path in unweighted graph |

# 5. Recursion and backtracking

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| Subsets | Copy and filter every mask | Recursive include/exclude | Backtracking with exactly two branches per item |
| Subsets II | Generate then deduplicate | Set of outputs | Sort and skip duplicates at the same depth |
| Permutations | Generate and deduplicate | Used array | Swap backtracking; skip duplicate values for unique variant |
| Combination sum | Enumerate all lists | Prune above target | Sorted candidates, choose/reuse with remaining target |
| Generate parentheses | Generate all strings | Reject invalid prefixes | Only add close when closes < opens |
| N-Queens | Place and scan conflicts | Column/diagonal sets | O(1) conflict checks with backtracking |
| Word search | Start every path without marks | Visited set | In-place mark and restore; path invariant prevents reuse |
| Restore IP addresses | All splits | Length pruning | Backtrack only valid segment lengths and values |
| Rat in maze | Explore all paths | Visited matrix | Backtrack with restoration and boundary checks |
| Catalan structures | Generate arbitrary trees | Recurrence | DP or Catalan formula when only count is required |

# 6. Linked lists

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| Reverse list | Copy values | Recursive reversal | Iterative previous/current/next pointers |
| Middle node | Count length | Two passes | Slow/fast pointers |
| Cycle detection | Visited set | Mark nodes if allowed | Floyd slow/fast pointers |
| Cycle entry | Store visit order | Find meeting then walk | Floyd: reset one pointer to head |
| Remove Nth from end | Count then remove | Two passes | Dummy node and fixed fast/slow gap |
| Palindrome list | Copy values | Reverse copy | Find middle, reverse half, compare, optionally restore |
| Reorder list | Repeated tail lookup | Array of nodes | Middle, reverse second half, weave |
| Merge two lists | Concatenate and sort | Array sort | Dummy-tail merge |
| Merge K lists | Concatenate and sort | Pairwise merge | Min heap or divide-and-conquer |
| Copy random list | Two-pass map | Interleaved clones | Clone between nodes, wire random, separate |
| Reverse k-group | Count each group | Stack group | Reverse pointers only when a complete group exists |
| Add numbers | Convert to integer | Digit arrays | Carry-based list addition; avoid numeric overflow |

# 7. Stack, queue, and heap

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| Min stack | Scan for minimum | Store pair with min | Auxiliary min stack or encoded values |
| Queue using stacks | Move all items per operation | Transfer only when needed | Two-stack amortized O(1) queue |
| Next greater element | Scan right | Precompute next | Monotonic decreasing stack |
| Daily temperatures | Scan future days | Heap | Monotonic stack of unresolved indexes |
| Largest rectangle | Expand every bar | Previous/next smaller arrays | Monotonic stack with width on pop |
| Sliding maximum | Scan each window | Heap with lazy deletion | Deque of decreasing values |
| Last stone weight | Sort repeatedly | Sorted multiset | Max heap |
| Top K frequent | Sort frequencies | Heap of size k | Bucket sort when frequency bounds are useful |
| Median stream | Sort all values | Balanced tree | Max heap lower half plus min heap upper half |
| Task scheduler | Simulate each time | Count frequencies | Max heap plus cooldown queue or frequency formula |
| Remove K digits | Try removals | DP | Monotonic increasing stack removes larger previous digits |
| Shortest subarray at least K | Enumerate | Sliding window only for positive values | Prefix sums plus monotonic deque with negative values |

# 8. Trees and BSTs

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| Depth | Recompute levels | DFS | One DFS returns one plus max child height |
| Invert | Copy nodes | BFS | Swap children recursively or iteratively |
| Same/symmetric | Serialize | Recursive compare | Pairwise recursion with null checks |
| Level order | DFS by depth | Queue | Process queue size per level |
| Right view | Store all levels | BFS last item | Right-first DFS first visit at depth |
| Diameter | Height per node | Memoized heights | Postorder height plus global diameter |
| Balanced tree | Height per node | Memoization | Return height or failure sentinel in one pass |
| LCA binary tree | Parent paths | Parent map | Recursive result propagation |
| LCA BST | General recursion | Parent paths | Use ordering to move left/right |
| Validate BST | Sort inorder | Inorder with previous | Recursive open range |
| Kth smallest | Collect/sort | Inorder array | Iterative inorder counter |
| Serialize | Store values only | Level order | Preorder with null markers is bijective |
| Build from traversals | Search root each time | Index map | Index map plus recursion boundaries |
| Flatten tree | Rebuild list | Reverse preorder | In-place preorder rewiring |
| Burning tree / distance K | Repeated DFS | Parent map | Build parent links then BFS |
| Vertical order | DFS coordinates | Map columns | BFS/priority ordering according to tie contract |

# 9. Graphs

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| DFS/BFS traversal | Repeated scans | Adjacency list | Visited set ensures each vertex/edge processed once |
| Number of islands | Re-scan islands | DFS/BFS marking | Flood-fill each unvisited land component |
| Rotting oranges | Rescan grid each minute | Queue sources | Multi-source BFS by levels |
| Shortest unweighted path | Enumerate paths | BFS | First visit is shortest distance |
| Dijkstra network delay | Enumerate paths | Repeated minimum scan | Min heap and stale-entry check for nonnegative weights |
| Course schedule | Repeated dependency removal | DFS states | Kahn indegrees or three-color DFS |
| Accounts merge | Compare all emails | Graph DFS | Union Find by shared email |
| Redundant connection | Search paths | DFS connectivity | Union Find detects edge joining same component |
| Cheapest flights K stops | Dijkstra without state | DP by stops | State includes number of edges; bounded Bellman-Ford or layered BFS |
| Word ladder | Enumerate paths | BFS transformations | Wildcard buckets reduce neighbor generation |
| Alien dictionary | Compare all words | Build constraints | Topological sort; invalid prefix must be rejected |
| Graph valid tree | DFS | Connected + edge count | Union Find or DFS with cycle and connectivity checks |
| MST | Enumerate spanning trees | Prim or Kruskal | Greedy safe edge under cut property |

# 10. Dynamic programming and greedy

| Problem | Brute | Better | Optimal / key invariant |
|---|---|---|---|
| Fibonacci / stairs | Recursion | Memoization | Rolling DP values |
| House robber | Choose/skip recursion | Memoization | `dp[i] = max(skip, take)` |
| Coin change | All combinations | Memoization | Bottom-up minimum for every amount |
| 0/1 knapsack | Enumerate subsets | 2D DP | 1D reverse-capacity DP |
| Target sum | Enumerate signs | Memoization | Subset-sum transformation where valid |
| LIS | Enumerate subsequences | O(n^2) DP | Tails plus binary search, O(n log n) |
| LCS | Recursive matches | Memoization | 2D DP on prefixes |
| Edit distance | All edits | Memoization | Insert/delete/replace recurrence |
| Decode ways | Recursive splits | Memoization | DP by valid one/two-digit endings |
| Unique paths | Recursion | 2D DP | 1D row-compressed DP or combinatorics |
| Word break | Partition recursion | Memoization | Reachable prefix DP or Trie |
| Jump game | Recursive jumps | DP reachability | Farthest reachable index greedy |
| Jump game II | Enumerate paths | DP | Greedy current range expansion |
| Gas station | Try every start | Prefix analysis | Reset start after deficit; total gas must cover cost |
| Candy | Repeated adjustments | Two arrays | Left-to-right and right-to-left requirements |
| Interval scheduling | Try combinations | DP | Sort by end and greedily keep earliest finish |
| Merge intervals | Repeated compare | Sorted scan | Merge with last interval after sorting |
| Non-overlap intervals | Remove arbitrary overlaps | DP | Greedy keep interval with earliest end |

# 11. Design and machine-coding solutions

## Parking lot

- Brute design: one large class with switches and conditionals.
- Better: separate vehicle, ticket, floor, spot, pricing, and payment components.
- Optimal production design: interfaces for spot allocation, pricing, payment, and notification; state transitions are explicit and persisted.
- Must discuss: concurrency at spot allocation, payment failure, ticket idempotency, lost tickets, and audit logs.

## Vending machine

- Brute: condition-heavy state checks.
- Better: state pattern for idle, selection, payment, dispensing, and refund.
- Optimal: typed money/stock abstractions, transaction boundary, idempotent payment, and recovery after power loss.

## Logging framework

- Brute: print directly from every class.
- Better: logger with levels and sinks.
- Optimal: async bounded queue, structured events, sampling, rotation, backpressure, redaction, and graceful shutdown.

## Pub/sub

- Brute: direct calls from publisher to subscribers.
- Better: in-memory topic map.
- Optimal: durable broker, consumer groups, offsets, replay, ordering scope, dead letters, backpressure, and at-least-once duplicate handling.

## LRU cache

- Brute: list scan and move, O(n).
- Better: ordered map, O(log n).
- Optimal: hash map plus doubly linked list, expected O(1). Add TTL and thread safety only when required.

## Ride sharing

- Brute: scan all available drivers.
- Better: grid buckets.
- Optimal: geospatial index, matching policy, state machine, payment idempotency, location freshness, surge rules, and event-driven updates.

# 12. High-frequency HLD answer checklist

For every large system question:

1. Clarify users, actions, and non-goals.
2. Estimate requests per second, storage, payload size, and growth.
3. Define availability, latency, consistency, and durability goals.
4. Sketch APIs and core data model.
5. Separate synchronous user path from asynchronous work.
6. Choose storage and indexes based on access patterns.
7. Explain cache keys, invalidation, and stampede control.
8. Explain queue semantics, ordering, retries, and replay.
9. Explain partitioning, replication, and hot keys.
10. Add authentication, authorization, encryption, and tenant isolation.
11. Add metrics, logs, traces, alerts, and SLOs.
12. Explain deployment, migration, rollback, and disaster recovery.
13. State the main trade-off and what you would improve next.

# 13. What is already fully executable

The following high-priority implementations are available in the repository workbooks:

- Arrays and hashing: Two Sum, stock profit, contains duplicate, product except self, majority, top K, longest consecutive.
- Strings and windows: valid parentheses, longest unique substring, minimum window.
- Linked lists: reverse, merge, cycle, remove Nth, merge K lists, reorder.
- Trees: level order, depth, diameter, LCA, BST validation, kth smallest, serialization.
- Search: binary search, rotated search, minimum rotated value, shipping capacity.
- Greedy/DP: Jump Game, Jump Game II, House Robber, Coin Change, LIS, Unique Paths.
- Graphs: islands, clone graph, course scheduling, rotting oranges, Union Find.
- Heaps/design: Kth largest, K closest, Trie, TimeMap, LRU, rate limiter.

# 14. Definition of a finished solution

Do not mark a problem complete until you can:

- state the problem and constraints,
- explain brute force,
- explain the better approach,
- derive the optimal approach,
- prove the invariant,
- implement it from a blank file,
- test edge cases,
- state complexity,
- explain a follow-up variation,
- and describe the production trade-off.
