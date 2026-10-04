# Meta Complete Preparation Master

## Scope

This is the broadest practical preparation checklist for Meta software engineering, AI engineering, applied AI, ML engineering, solutions engineering, and FDE roles in London and other European offices.

It is designed to cover the areas that commonly appear across different teams. It cannot guarantee an exact interview loop or offer; the recruiter and hiring team determine the actual scope.

## 1. Algorithms and data structures

### Core patterns

- Arrays, strings, hashing, frequency maps, prefix sums.
- Sorting, two pointers, fast and slow pointers.
- Sliding windows and monotonic queues.
- Stacks, queues, heaps, and monotonic stacks.
- Linked lists and pointer manipulation.
- Binary trees, BSTs, recursion, DFS, BFS, and serialization.
- Graph traversal, topological sort, shortest path, and Union Find.
- Binary search and binary search over an answer space.
- Greedy algorithms and interval scheduling.
- One-dimensional and two-dimensional dynamic programming.
- Backtracking, tries, bit manipulation, and design data structures.

### High-priority problems

- Two Sum, 3Sum, Four Sum.
- Group Anagrams, Top K Frequent, Product Except Self.
- Subarray Sum Equals K, Longest Consecutive Sequence.
- Longest Substring Without Repeating Characters.
- Minimum Window Substring and Sliding Window Maximum.
- Trapping Rain Water and Largest Rectangle in Histogram.
- Merge Intervals, Meeting Rooms II, Insert Interval.
- Reverse List, Reorder List, Copy Random List, Merge K Lists.
- Level Order, Right Side View, Diameter, LCA, Validate BST.
- Serialize/Deserialize Tree and Construct Tree from Traversals.
- Number of Islands, Clone Graph, Course Schedule.
- Word Ladder, Network Delay Time, Cheapest Flights.
- Binary Search, Rotated Search, Koko Eating Bananas.
- Kth Largest, Median from Data Stream, K Closest Points.
- House Robber, Coin Change, Word Break, LIS, Edit Distance.
- Subsets, Permutations, Combination Sum, N-Queens, Word Search.
- LRU Cache, Trie, Time-Based Key-Value Store.

### Interview standard

- Solve two medium problems in 60-70 minutes.
- Explain brute force, optimization, invariant, complexity, and tests.
- Write compilable code without depending on autocomplete.
- Test empty input, one element, duplicate values, negative values, overflow, and large input.

## 2. SQL and data work

Practice writing and explaining:

1. Second-highest salary.
2. Top three salaries per department.
3. Customers with no orders.
4. Duplicate records and deduplication with window functions.
5. Seven-day rolling average.
6. Daily active users and weekly active users.
7. Retention cohorts.
8. Conversion funnel drop-off.
9. Sessionization from event timestamps.
10. Latest record per user.
11. Gaps and islands.
12. Recursive organization hierarchy.
13. Slowly changing dimension logic.
14. Join explosion diagnosis.
15. Query performance using indexes and query plans.

Know:

- Inner, left, right, and full joins.
- `GROUP BY`, `HAVING`, `CASE`, CTEs, subqueries.
- Window functions, ranking, lag/lead, and frames.
- Null behavior and duplicate handling.
- Transactions, isolation, indexes, partitioning, and normalization.

## 3. Programming language and code quality

### C++

- References, pointers, RAII, smart pointers, move semantics.
- Stack versus heap and object lifetime.
- Rule of three/five/zero.
- STL containers and their complexity.
- Iterators, lambdas, templates, and const correctness.
- Undefined behavior, iterator invalidation, and memory leaks.
- Threads, mutexes, condition variables, atomics, and race conditions.
- Profiling, sanitizers, compiler warnings, and unit testing.

### Python

- Lists, dictionaries, sets, tuples, generators, and comprehensions.
- Iterators, decorators, context managers, exceptions, and typing.
- Async IO versus threads versus processes.
- GIL implications and CPU-bound versus IO-bound work.
- Packaging, virtual environments, testing, logging, and profiling.
- FastAPI or equivalent API patterns and validation.

### General engineering

- API contracts and backward compatibility.
- Input validation and error handling.
- Testable functions and dependency boundaries.
- Unit, integration, contract, load, and property-based tests.
- Code review: correctness, security, observability, maintainability.

## 4. Object-oriented and component design

Practice designing:

- Parking lot.
- Elevator system.
- Library system.
- Rate limiter.
- LRU and LFU cache.
- Notification service.
- File storage abstraction.
- Job scheduler.
- Logging framework.
- Metrics collector.
- Chess or board-game engine.
- Document processing pipeline.

Discuss:

- Interfaces and responsibilities.
- Composition versus inheritance.
- Extensibility and testability.
- Thread safety and lifecycle management.
- Error handling and persistence boundaries.

## 5. Operating systems and concurrency

Know how to explain:

- Processes versus threads.
- Context switching and scheduling.
- Virtual memory, pages, TLB, and page faults.
- Stack, heap, memory fragmentation, and allocation.
- Deadlock conditions and prevention.
- Mutex, semaphore, read/write lock, and atomic operation.
- Race conditions and happens-before relationships.
- Producer-consumer queues.
- Thread pools and backpressure.
- Signals, file descriptors, and basic Linux debugging.

Practice:

- Thread-safe bounded queue.
- Concurrent counter with correct semantics.
- Producer-consumer pipeline.
- Parallel map with bounded workers.
- Idempotent job execution.

## 6. Networking and web systems

Know:

- TCP versus UDP.
- HTTP methods, status codes, headers, cookies, and caching.
- TLS and certificate validation at a high level.
- DNS, proxies, load balancers, and CDNs.
- REST versus gRPC versus message queues.
- Webhooks, retries, idempotency, and signature verification.
- Long polling, server-sent events, and WebSockets.
- Authentication, authorization, OAuth, JWT, and service credentials.
- Rate limiting, timeouts, circuit breakers, and connection pools.

Implement or design:

- Authenticated API endpoint.
- Signed webhook receiver.
- Idempotent payment or order endpoint.
- Streaming response endpoint.
- Multi-tenant rate limiter.

## 7. Distributed systems and system design

For every design, state requirements before components.

### Core concepts

- Availability, consistency, partition tolerance, and trade-offs.
- Replication, sharding, partition keys, and rebalancing.
- Leader/follower and quorum concepts.
- Strong versus eventual consistency.
- Caches, invalidation, TTL, and stampede control.
- Queues, streams, consumer groups, ordering, replay, and dead letters.
- Idempotency and exactly-once illusions.
- Backpressure, load shedding, and graceful degradation.
- Observability, SLOs, SLIs, error budgets, and incident response.
- Schema evolution, migrations, backups, and disaster recovery.

### Design prompts

- News feed.
- Chat and messaging.
- Photo or video sharing.
- Notification platform.
- Search autocomplete.
- Distributed URL shortener.
- File storage and sharing.
- Metrics and logging platform.
- Rate limiter.
- Feature flag service.
- Job scheduler.
- Payment or billing events.
- Abuse detection pipeline.
- Real-time collaboration tool.
- Global API with regional data residency.

## 8. Machine learning fundamentals

Know how to explain:

- Classification, regression, clustering, and ranking.
- Train, validation, and test splits.
- Leakage, overfitting, regularization, and cross-validation.
- Precision, recall, F1, ROC-AUC, PR-AUC, calibration.
- Class imbalance and threshold selection.
- Feature engineering, normalization, and missing data.
- Offline versus online metrics.
- Distribution shift, drift, and feedback loops.
- A/B testing, statistical significance, and guardrail metrics.
- Model interpretability and error analysis.
- Batch, online, and streaming inference.

## 9. LLM and applied AI engineering

### Architecture

- Request gateway and authentication.
- Model router and provider abstraction.
- Prompt templates and version control.
- Conversation state and context management.
- Tool calling and permission boundaries.
- Retrieval ingestion, chunking, metadata, embeddings, vector search, reranking.
- Structured output validation and post-processing.
- Streaming, batching, caching, fallbacks, and cost controls.

### Evaluation

- Golden datasets and representative slices.
- Exact match, semantic similarity, groundedness, citation correctness.
- Retrieval precision, recall, MRR, and NDCG.
- Human review, pairwise preference, and rubric design.
- Regression tests for prompts and model versions.
- Latency, throughput, token usage, cost, and failure rate.
- Online feedback and safe experimentation.

### Safety and privacy

- Prompt injection and indirect injection.
- Sensitive data leakage and PII redaction.
- Excessive tool permissions and sandboxing.
- Tenant isolation and document-level access control.
- Data retention, deletion, audit logs, and regional residency.
- Jailbreaks, unsafe output, refusal, and human escalation.
- Untrusted retrieved content and tool output validation.

### AI system-design prompts

- Enterprise RAG assistant.
- Multi-tenant LLM gateway.
- Safe tool-using agent.
- LLM evaluation platform.
- Model serving and routing platform.
- Conversation memory service.
- AI support-ticket summarizer.
- Semantic search and reranking service.
- AI moderation or abuse classifier.
- Prompt and model configuration service.

## 10. FDE and customer delivery

Prepare examples for:

- Ambiguous requirement discovery.
- Rapid proof of concept.
- Productionizing a prototype.
- Legacy API integration.
- Customer data-quality problems.
- Security or privacy limitation.
- Production incident and communication.
- Scope negotiation.
- Cross-functional disagreement.
- Measurable customer impact.

Practice this delivery flow:

1. Clarify the business goal.
2. Identify users and workflow.
3. Define success metrics.
4. Map data sources and permissions.
5. Build the smallest safe version.
6. Add tests and evaluation.
7. Instrument logs, metrics, and traces.
8. Roll out gradually.
9. Document operations and ownership.
10. Review impact and next iteration.

## 11. Behavioral preparation

Prepare STAR stories for:

- Ownership.
- Customer obsession.
- Technical disagreement.
- Failure and learning.
- Difficult deadline.
- Production incident.
- Ambiguous project.
- Influence without authority.
- Mentoring or collaboration.
- Security, privacy, or ethical decision.
- Cost, latency, quality, or reliability improvement.
- A project that changed direction.

Each story should answer:

- What was the situation?
- What specifically did you own?
- What decision did you make?
- What was difficult?
- What was the measurable result?
- What would you do differently?

## 12. Mock interview program

### Mock 1: coding

Two medium problems in 70 minutes. Record the explanation and review correctness, edge cases, and communication.

### Mock 2: debugging

Given failing logs and an API/data-flow diagram, identify the hypothesis, add instrumentation, isolate the failure, and propose a fix.

### Mock 3: system design

Design a multi-tenant RAG assistant in 45 minutes. Include scale, permissions, evaluation, cost, and incident recovery.

### Mock 4: FDE

Turn a vague customer request into a two-week MVP plan with milestones, risks, and success metrics.

### Mock 5: behavioral

Answer ten STAR questions in under 60 minutes with specific results and no vague claims.

### Mock 6: full loop

Coding, system design, AI deep dive, debugging, customer presentation, and behavioral round on separate sessions.

## 13. Final readiness standard

Before applying or interviewing, you should be able to:

- Solve the Priority A coding list without looking up patterns.
- Complete two medium coding problems in one hour.
- Design an AI production system in 45 minutes.
- Explain retrieval, evaluation, safety, and model-serving trade-offs.
- Debug API and data problems methodically.
- Write practical SQL queries with window functions.
- Discuss concurrency, networking, storage, and reliability.
- Give ten specific behavioral stories.
- Explain your strongest project to engineers and customers.
- Ask the recruiter about the exact team, level, loop, language, and role expectations.
