# Personal Guidance 12-Week Plan

## Purpose

This plan is based on the attached curriculum and is adapted for modern software engineering, AI/ML, GenAI, LLM, FDE, and international interviews.

It keeps the useful structure:

- language fundamentals,
- DSA and pattern recognition,
- OS, DBMS, networking,
- OOP and design,
- projects,
- system design,
- resume and profile quality,
- mock evaluations,
- job search and interview delivery.

It adds current expectations:

- production-grade LLM systems,
- evaluation and observability,
- cloud and on-prem deployment,
- security and privacy,
- agentic systems,
- SQL and data pipelines,
- honest, verifiable resume evidence,
- international applications and work authorization.

## Scope clarification

This file is the study roadmap. It contains solution strategies, practice order,
weekly deliverables, and evaluation gates; it does not contain full code for
every problem in the attached curriculum. Use these companion resources for
the detailed solution work:

- [solution_index_and_three_approach_matrix.md](solution_index_and_three_approach_matrix.md): brute, better, optimal strategy, invariants, and complexity across the problem families.
- [interview_explanations_and_answer_scripts.md](interview_explanations_and_answer_scripts.md): detailed interview reasoning for priority problems.
- [top_50_coding_solutions.cpp](top_50_coding_solutions.cpp): executable C++ implementations for the core set.
- [lld_hld_interview_answers.md](lld_hld_interview_answers.md): detailed LLD/HLD answer frameworks, APIs, data models, trade-offs, and AI system designs.
- [cs_fundamentals_interview_answers.md](cs_fundamentals_interview_answers.md): OS, concurrency, DBMS, SQL, networking, OOP, cloud, API, observability, and debugging answers.

No document can make an interviewer hire someone automatically. SDE2/SDE3
readiness requires independently solving, testing, explaining, and defending
the trade-offs in these resources.

## Important correction to the attached advice

Never invent employment history, change non-technical work into false software experience, or copy another person’s resume. That can fail background checks and destroy trust. Instead, present transferable work accurately and add genuine software projects, measurable outcomes, open-source work, and technical evidence.

# Three-approach method for every coding problem

For every problem in this plan, write one page using this structure:

## Approach 1: Brute force

- State the direct idea.
- Explain why it is correct.
- Give worst-case time and space complexity.
- Identify the repeated work or bottleneck.
- Give one input where it becomes too slow.

## Approach 2: Better

- Remove one major source of repeated work.
- Explain the data structure or preprocessing.
- State the invariant.
- Give complexity and trade-offs.
- Explain why it is still not the best available solution.

## Approach 3: Optimal or production-appropriate

- State the pattern and assumptions.
- Explain the invariant or recurrence.
- Give a short correctness proof.
- State time, auxiliary space, and output space separately.
- Test empty, smallest, duplicate, negative, maximum, and invalid cases.
- Mention when a theoretically faster solution is less suitable in production.

## Example: Two Sum

### Brute force

Try every pair and return the pair whose sum equals the target.

- Time: O(n^2).
- Extra space: O(1).
- Failure mode: too slow for large arrays.

### Better

Sort pairs of values and original indexes, then use two pointers.

- Time: O(n log n).
- Extra space: O(n) if original indexes must be preserved.
- Trade-off: sorting changes order and is unnecessary if one query is required.

### Optimal

Store values already seen in a hash map. For value `x`, look for `target - x` before inserting `x`.

- Expected time: O(n).
- Extra space: O(n).
- Invariant: the map contains exactly the earlier values.
- Edge cases: duplicate values and no answer.

# Weekly program

## Week 1: Orientation, language, Git, and baseline

### Study

- Choose Python for AI/ML roles or C++/Java if the target role requires it.
- Variables, types, expressions, conditionals, loops, functions, methods, collections.
- Classes, objects, encapsulation, inheritance, polymorphism, abstraction.
- Git branches, commits, pull requests, README writing, issues, and code review.
- Big-O time and space complexity.

### Practice

- Reverse a string.
- Count frequencies.
- Prime, GCD, LCM, divisors, Armstrong number.
- Reverse integer and palindrome number.
- Write a small CLI utility with tests.

### Deliverables

- GitHub profile with a professional README.
- LeetCode or equivalent profile.
- One language revision repository.
- Baseline assessment of five coding problems.
- Target-role list with skills and locations.

### Gate

Explain your language’s arrays, hash map, stack, queue, class, exception, and test concepts without notes.

## Week 2: Searching, sorting, arrays, and prefixes

### Topics

- Linear and binary search.
- Search first/last occurrence and insertion position.
- Rotated arrays and binary search on the answer.
- Selection, insertion, merge, quick, heap, counting, and radix sort.
- Prefix sums, difference arrays, two pointers, and array invariants.

### Problems

- Find first and last position.
- Search insert position.
- Search rotated array.
- Find minimum in rotated array.
- Find peak element.
- Inversion count.
- Next permutation.
- Maximum subarray.
- Rotate array.
- Equilibrium point.
- Missing number.
- Maximum product subarray.

### Three-approach requirement

For each search problem, write linear scan, sorted/preprocessed approach, and binary-search approach. Prove why the discarded half cannot contain the answer.

### Gate

Solve a binary-search-on-answer problem and explain monotonic feasibility.

## Week 3: Strings, hashing, sliding windows, and recursion

### Topics

- Character frequency and canonical signatures.
- Prefix/suffix processing.
- Two pointers and sliding windows.
- Recursion tree, base case, state, and backtracking.
- Duplicate handling and output-size lower bounds.

### Problems

- Valid anagram.
- Isomorphic strings.
- Longest substring without repeating characters.
- Permutation in string.
- Find all anagrams.
- Longest repeating character replacement.
- Minimum window substring.
- Container with most water.
- Count subarrays with a condition.
- Generate parentheses.
- Combinations, subsets, and permutations.
- Word break.
- Longest palindromic substring.

### Scenario

Given a large stream of text, explain what can be processed online, what must be stored, and how memory grows.

### Gate

For one sliding-window problem, state exactly what makes a window valid and why every pointer moves only forward.

## Week 4: Linked lists, stacks, queues, and heaps

### Topics

- Pointer ownership and mutation.
- Fast/slow pointers.
- Monotonic stacks and queues.
- Priority queues and top-K problems.
- Implement stack and queue using arrays, linked lists, and each other.

### Problems

- Reverse linked list.
- Middle of linked list.
- Linked-list cycle and cycle entry.
- Remove Nth node from end.
- Palindrome linked list.
- Reverse nodes in k-group.
- Copy list with random pointer.
- Add two numbers.
- Min stack.
- Next greater element.
- Largest rectangle in histogram.
- Sliding-window maximum.
- K closest points.
- Median from data stream.
- Merge K sorted lists.

### Scenario

Design a thread-safe bounded queue. Explain blocking, backpressure, shutdown, and what happens when the consumer is slower.

### Gate

Implement LRU cache and explain why the hash map plus doubly linked list gives expected O(1) operations.

## Week 5: Trees, BST, graphs, and Union Find

### Topics

- Recursive versus iterative traversal.
- Inorder, preorder, postorder, level order, zigzag.
- BST invariants and range validation.
- BFS, DFS, visited state, and connected components.
- Topological ordering and cycle detection.
- Dijkstra and Union Find.

### Problems

- Maximum depth.
- Invert tree.
- Same and symmetric tree.
- Level order and right-side view.
- Diameter and balanced tree.
- Lowest common ancestor.
- Validate BST and kth smallest.
- Serialize/deserialize.
- Construct tree from traversals.
- Number of islands.
- Flood fill and rotting oranges.
- Clone graph.
- Course schedule I and II.
- Network delay time.
- Accounts merge and redundant connection.
- Word ladder.

### Scenario

Explain how to process a graph that is too large for memory on one machine. Discuss partitioning, distributed traversal, duplicate work, and consistency.

### Gate

Design a graph API and state whether the graph is directed, weighted, static, or dynamic before choosing an algorithm.

## Week 6: Dynamic programming, greedy, and intervals

### Topics

- State definition, transition, base case, iteration order.
- Memoization versus tabulation.
- Space compression.
- Greedy exchange argument.
- Interval sorting and event sweeps.

### Problems

- Fibonacci and climbing stairs.
- House robber I and II.
- Coin change and coin change II.
- 0/1 knapsack.
- Target sum.
- Longest increasing subsequence.
- Longest common subsequence.
- Edit distance.
- Decode ways.
- Unique paths.
- Jump game I and II.
- Gas station.
- Candy.
- Merge intervals.
- Meeting rooms I and II.
- Non-overlapping intervals.

### Gate

For every DP solution, explain what one cell means in plain English. If you cannot define the state, do not code yet.

## Week 7: OS, concurrency, DBMS, and SQL

### Operating systems

- Process, PCB, lifecycle, scheduling, context switching.
- User mode and kernel mode.
- Virtual memory, paging, page faults, TLB, and replacement.
- Threads versus processes.
- Race conditions, critical sections, mutexes, semaphores.
- Deadlock conditions, prevention, avoidance, and recovery.
- Producer-consumer and reader-writer problems.

### DBMS

- ER diagrams and relational modeling.
- Primary/foreign keys and constraints.
- Normalization and denormalization.
- Indexes, B+ trees, hash indexes, LSM trees, Bloom filters.
- ACID, isolation levels, serializability, locks, and MVCC.
- MySQL/PostgreSQL versus document, key-value, column, graph, and time-series stores.

### SQL practice

- Second-highest salary.
- Top three per department.
- Latest record per user.
- Deduplicate with row numbers.
- Seven-day rolling average.
- Daily and weekly active users.
- Cohort retention.
- Sessionization.
- Gaps and islands.
- Join explosion diagnosis.

### Gate

Explain a deadlock with a concrete sequence and write five SQL queries using window functions.

## Week 8: Networking, APIs, cloud, and deployment

### Topics

- OSI model and TCP/IP layers.
- IPv4/IPv6, DNS, TCP handshake, UDP, HTTP, TLS.
- REST, GraphQL, gRPC, polling, SSE, WebSockets.
- Load balancers, proxies, CDNs, and service discovery.
- Authentication, authorization, OAuth, JWT, and secrets.
- Timeouts, retries, exponential backoff, jitter, rate limits.
- Docker, CI/CD, health checks, Kubernetes basics.

### Practice

- Authenticated API.
- Signed webhook receiver.
- Idempotent order endpoint.
- Streaming response endpoint.
- Dockerized service with tests and health checks.

### Gate

Explain what happens from entering a URL to receiving the response, including DNS, connection, TLS, HTTP, load balancing, and application processing.

## Week 9: ML and deep learning

### Topics

- Supervised, unsupervised, and self-supervised learning.
- Train/validation/test, leakage, bias/variance, regularization.
- Precision, recall, F1, ROC-AUC, PR-AUC, calibration.
- Class imbalance, thresholding, error analysis.
- Neural networks, loss, backpropagation, optimizers.
- CNNs, RNNs, attention, transformers.
- Embeddings and similarity search.
- PyTorch/TensorFlow training and reproducibility.

### Project

Build a small ML application with a baseline, data split, metric rationale, error analysis, model card, and reproducible training script.

### Gate

Explain why a model improved or regressed using evidence from data, features, training, and evaluation.

## Week 10: LLM, RAG, agents, and evaluation

### Topics

- Tokens, context windows, embeddings, transformer intuition.
- Prompting and structured outputs.
- RAG ingestion, chunking, metadata, retrieval, reranking.
- Fine-tuning versus RAG versus deterministic workflows.
- Tool calling and agent state.
- Prompt injection, PII, tenant isolation, and safe tools.
- Evaluation datasets, retrieval recall, MRR, groundedness, citation correctness.
- Latency, token cost, caching, streaming, fallback, and model routing.

### Project

Build a production-style multi-tenant RAG assistant with permissions, citations, evaluation, logs, cost tracking, and a threat model.

### Gate

Show retrieval failure and generation failure as separate traces and explain a fix for each.

## Week 11: HLD, LLD, FDE, and project defense

### LLD topics

- Classes, interfaces, composition, SOLID, DRY, KISS, YAGNI, GRASP.
- UML class and sequence diagrams.
- Factory, Builder, Adapter, Decorator, Proxy, Facade, Strategy, Observer, State, Command.
- Thread safety, validation, persistence, and testability.

### HLD prompts

- News feed.
- Chat system.
- Ticket booking.
- Ride sharing.
- Object storage.
- URL shortener.
- Web crawler.
- Distributed rate limiter.
- Notification system.
- Enterprise RAG.
- LLM gateway.
- Evaluation platform.
- SOC AI copilot.

### FDE practice

- Discovery call.
- Requirements document.
- Two-week MVP plan.
- Demo to technical stakeholder.
- Demo to executive stakeholder.
- Production incident update.
- Security limitation explanation.

### Gate

Defend two projects from your own resume in technical depth, including trade-offs and one failure.

## Week 12: Applications, mocks, and final revision

### Mock loop

- Two coding problems in 70 minutes.
- One SQL and debugging round.
- One LLD or machine-coding task.
- One 45-minute HLD.
- One ML/LLM deep dive.
- One FDE customer scenario.
- One behavioral round.

### Resume and profile

Use truthful, measurable evidence:

- Problem.
- Your action.
- Technical design.
- Result.
- Metric.
- Tools and trade-offs.

### Job search

- Tailor the resume to the exact role.
- Build a target list by role, level, location, salary, sponsorship, and skill match.
- Ask for referrals with a specific project and role link.
- Contact recruiters with a short value statement.
- Track applications and follow-ups.
- Confirm language, onsite, travel, sponsorship, and interview format.

# Three-approach solution catalog

Use this catalog with the attached problem list. The full code should be practiced in your chosen language; the explanation should always compare approaches.

## Math and number problems

- Brute: direct loops, repeated divisibility, or trial multiplication.
- Better: stop at square root, cache divisors, or use prefix computation.
- Optimal: sieve for many primes, Euclidean algorithm for GCD, fast exponentiation, modular arithmetic.
- Watch: overflow, zero, negative values, and input bounds.

## Sorting and searching

- Brute: scan or compare all pairs.
- Better: sort or preprocess once.
- Optimal: binary search, merge sort counting, heap, Quickselect, or binary search on a monotonic answer.
- Prove: why the discarded region cannot contain a valid answer.

## Arrays and hashing

- Brute: nested subarrays or pair comparisons.
- Better: sort, prefix sums, or frequency arrays.
- Optimal: hash maps, sliding windows, two pointers, or in-place marking when modification is allowed.
- Watch: duplicates, negative values, mutation, and expected versus worst-case hashing.

## Strings

- Brute: generate substrings or repeated concatenation.
- Better: frequency counts, KMP/Z algorithm, rolling hash, or dynamic programming.
- Optimal: select by constraints; linear is not automatically best if alphabet, memory, or Unicode changes.
- Watch: encoding, case, whitespace, and integer conversion overflow.

## Linked lists

- Brute: copy values into an array.
- Better: hash visited nodes or calculate length first.
- Optimal: pointer invariants, fast/slow pointers, in-place reversal, dummy nodes, and divide-and-conquer merging.
- Watch: ownership, cycles, null pointers, and losing the remaining list after rewiring.

## Trees and graphs

- Brute: repeated scans or recomputation.
- Better: memoization, parent maps, or adjacency preprocessing.
- Optimal: one-pass DFS, BFS, topological sort, Dijkstra, or Union Find according to graph properties.
- Watch: directed versus undirected, weighted versus unweighted, recursion depth, and visited state.

## Dynamic programming

- Brute: enumerate choices recursively.
- Better: memoize repeated states.
- Optimal: bottom-up DP, rolling memory, or a greedy proof when one exists.
- Watch: state meaning, transition order, impossible states, and output reconstruction.

## Heaps and greedy

- Brute: sort repeatedly.
- Better: sort once or use a heap.
- Optimal: bounded heap, two heaps, event sweep, or exchange-argument greedy.
- Watch: tie-breaking, stale heap entries, and whether the greedy choice is actually provable.

# Latest production additions

These topics should be added to older DSA and system-design material:

- LLM evaluation and regression gates.
- Retrieval permissions and tenant isolation.
- Prompt injection and indirect injection.
- Structured outputs and schema validation.
- Tool-call authorization and human approval.
- Token budgets and per-tenant cost attribution.
- Model routing and fallback quality contracts.
- RAG freshness, deletion, and index versioning.
- Tracing across retrieval, model, tools, and databases.
- p95/p99 latency and queue backpressure.
- Idempotency and replay-safe event processing.
- Data lineage, model lineage, and reproducibility.
- Kubernetes GPU scheduling and model-serving cold starts.
- Privacy, auditability, data residency, and secure logging.

# Project plan

## Project 1: Backend or data project

Build an authenticated API with a database, tests, logging, pagination, retry behavior, and Docker deployment.

## Project 2: Production RAG

Build ingestion, permissions, hybrid retrieval, citations, evaluation, observability, and cost reporting.

## Project 3: AI operations project

Build a model router, evaluation runner, rate limiter, or SOC copilot with threat model and incident playbook.

For every project publish:

- README.
- Architecture diagram.
- API examples.
- Data model.
- Test strategy.
- Evaluation report.
- Load or latency results.
- Threat model.
- Failure modes.
- Limitations.
- Deployment instructions.

# Evaluation gates

## Gate 1: fundamentals

Pass when you can implement basic data structures and explain complexity.

## Gate 2: patterns

Pass when you can recognize the pattern before coding and solve medium problems under time pressure.

## Gate 3: engineering

Pass when you can write tested APIs, SQL, logs, and deployment configuration.

## Gate 4: AI production

Pass when you can measure retrieval and generation separately and defend safety and cost decisions.

## Gate 5: interview

Pass when you can solve, design, debug, communicate, and answer behavioral questions without notes.

# Final rule

Do not finish a topic by watching a video. Finish it by producing working code, a measured experiment, a design, a test, or an explanation in your own words.
