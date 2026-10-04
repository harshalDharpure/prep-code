# CS Fundamentals Interview Answers

This workbook covers the remaining Computer Science fundamentals from the 12-week plan: Operating Systems, concurrency, DBMS, SQL, networking, OOP, APIs, cloud basics, and debugging.

Use the answer pattern: definition -> intuition -> example -> trade-off -> failure mode.

# Part 1: Operating Systems

## 1. Process versus thread

A process has its own virtual address space and operating-system resources. A thread is an execution path inside a process and usually shares the process’s memory and files. Processes provide stronger isolation but have higher creation and communication cost. Threads are cheaper for shared-memory concurrency but require synchronization.

**Scenario:** Use processes to isolate untrusted workloads or failures; use threads for parallel work that benefits from shared memory and controlled synchronization.

## 2. What happens during a context switch?

The operating system saves the running thread’s CPU state, selects another runnable thread, restores its state, and changes execution context. It may also disturb caches and translation lookaside buffers. Context switches are not free, so excessive fine-grained threading can reduce throughput.

## 3. User mode versus kernel mode

User mode restricts direct access to hardware and protected memory. Kernel mode allows the OS to perform privileged operations. A system call or interrupt transitions from user mode to kernel mode through a controlled entry point and returns after the operation.

## 4. Process lifecycle

Typical states are new, ready, running, blocked/waiting, and terminated. A process moves to waiting when it needs IO or a resource, and returns to ready when the event completes. Scheduling chooses among ready tasks.

## 5. Scheduling algorithms

- FCFS: simple but can create convoy effects.
- Shortest job first: minimizes average waiting when burst lengths are known.
- Round robin: fair interactive scheduling with a time quantum.
- Priority scheduling: supports importance but may starve low-priority tasks.
- Multilevel feedback queue: adapts priority based on behavior.

The right choice balances latency, fairness, throughput, and predictability.

## 6. Virtual memory

Virtual memory gives each process an address space that the MMU maps to physical frames through page tables. A page fault occurs when a required page is absent from physical memory. The OS loads it from backing storage, possibly evicting another page.

**Performance:** TLB hits are fast; TLB misses require page-table walks. Excessive page faults can cause thrashing.

## 7. Paging versus segmentation

Paging uses fixed-size blocks and avoids external fragmentation but may waste space inside a page. Segmentation reflects logical variable-sized regions such as code, stack, and data but can suffer external fragmentation. Modern systems primarily rely on paging with protection metadata.

## 8. Mutex versus semaphore

A mutex protects ownership of a critical section and should be unlocked by its owner. A semaphore is a counter used to control access to a number of permits or coordinate events. A binary semaphore is not automatically equivalent to an ownership-aware mutex.

## 9. Race condition

A race occurs when correctness depends on the timing of unsynchronized operations on shared state. Fixes include mutexes, atomics, immutable data, message passing, or redesigning ownership.

**Example:** `counter++` is usually read-modify-write, not one indivisible operation.

## 10. Deadlock

Deadlock requires mutual exclusion, hold-and-wait, no preemption, and circular wait. Prevent it by fixed lock ordering, avoiding nested locks, timeouts, lock acquisition protocols, or reducing shared mutable state.

**Interview scenario:** Two threads each hold one lock and wait for the other. A consistent global ordering prevents this cycle.

## 11. Producer-consumer problem

Use a bounded queue protected by a mutex, a condition variable for not-empty, and another for not-full. Producers wait when full; consumers wait when empty. Shutdown must wake all waiters and prevent new work from being accepted.

## 12. Atomicity, visibility, and ordering

Atomicity means an operation cannot be observed halfway. Visibility means one thread eventually sees another’s write. Ordering describes which operations can be observed before others. Locks provide mutual exclusion and ordering; atomics provide specific guarantees depending on memory order.

## 13. Starvation and fairness

Starvation means a task waits indefinitely while others continue. Fair queues, aging priorities, bounded lock acquisition, and admission policies improve fairness. Fairness can reduce peak throughput, so define the product requirement.

# Part 2: DBMS and SQL

## 14. Why use a database?

A database provides durable storage, query capability, concurrency control, recovery, constraints, and access management. The design should begin from access patterns and correctness requirements, not only from the data structure.

## 15. Primary key and foreign key

A primary key uniquely identifies a row. A foreign key references another table’s key and maintains referential integrity. Choose stable keys, define deletion behavior, and index frequent foreign-key access paths.

## 16. Normalization versus denormalization

Normalization reduces duplication and update anomalies by separating facts into related tables. Denormalization duplicates data to reduce read joins or improve read latency. Denormalization requires a consistency and update strategy.

## 17. ACID

- Atomicity: a transaction is all-or-nothing.
- Consistency: constraints remain valid.
- Isolation: concurrent transactions behave according to the isolation level.
- Durability: committed data survives failure.

ACID does not mean every transaction is globally serializable or infinitely available.

## 18. Isolation levels

- Read uncommitted: dirty reads possible.
- Read committed: prevents dirty reads but may allow non-repeatable reads.
- Repeatable read: stronger repeated-read behavior, implementation-dependent details.
- Serializable: behaves as if transactions ran one at a time, usually with lower concurrency.
- Snapshot/MVCC: readers use versions, reducing blocking but requiring conflict handling.

## 19. Indexes

An index is an additional structure that speeds selected access patterns at the cost of storage and write work. B+ trees support ordered lookup and range scans. Hash indexes are useful for equality. LSM trees optimize write-heavy workloads through sequential writes and compaction.

## 20. Composite index order

For an index on `(tenant_id, created_at)`, queries filtering by tenant and range-scanning time can use the index efficiently. The leftmost-prefix rule means a query only on `created_at` may not benefit as expected. Validate with the query plan.

## 21. Transactions and deadlocks

Keep transactions short, access tables in a consistent order, index the rows being locked, and retry safely after deadlock detection. Never retry a non-idempotent external side effect merely because a database transaction was retried.

## 22. SQL: latest row per user

```sql
WITH ranked AS (
    SELECT
        e.*,
        ROW_NUMBER() OVER (
            PARTITION BY user_id
            ORDER BY created_at DESC, id DESC
        ) AS row_number
    FROM events e
)
SELECT *
FROM ranked
WHERE row_number = 1;
```

The tie-breaker makes the result deterministic.

## 23. SQL: top three salaries per department

```sql
WITH ranked AS (
    SELECT
        employee_id,
        department_id,
        salary,
        DENSE_RANK() OVER (
            PARTITION BY department_id
            ORDER BY salary DESC
        ) AS salary_rank
    FROM employees
)
SELECT *
FROM ranked
WHERE salary_rank <= 3;
```

Use `DENSE_RANK` when equal salaries should share a rank; use `ROW_NUMBER` when exactly three rows are required.

## 24. SQL: rolling average

```sql
SELECT
    day,
    AVG(value) OVER (
        ORDER BY day
        ROWS BETWEEN 6 PRECEDING AND CURRENT ROW
    ) AS seven_row_average
FROM daily_metrics;
```

Clarify whether the requirement is seven rows or seven calendar days with missing dates filled.

## 25. SQL: duplicate removal

Use `ROW_NUMBER()` partitioned by the business identity and ordered by the preferred record. Before deleting, inspect the rows and define foreign-key and audit consequences.

## 26. Join explosion

A many-to-many join can multiply rows and inflate sums. Diagnose by checking cardinality before and after each join, pre-aggregating at the required grain, and validating counts with known examples.

## 27. RDBMS versus NoSQL

Use a relational database when transactions, joins, constraints, and flexible querying matter. Use key-value stores for predictable key access and high scale, document stores for aggregate-shaped data, column stores for analytics, graph stores for relationship traversal, and time-series stores for time-indexed metrics. Do not choose by brand; choose by access pattern and consistency needs.

## 28. Replication and partitioning

Replication copies data for availability and read scale. Partitioning divides data across nodes for write and storage scale. A good partition key distributes load and keeps common queries local. Hot keys, rebalancing, cross-partition transactions, and replica lag are major risks.

# Part 3: Computer Networks

## 29. OSI and TCP/IP models

The OSI model is a conceptual seven-layer model. The practical TCP/IP stack groups responsibilities into link, internet, transport, and application layers. Use models to reason about where addressing, reliability, routing, and application semantics live.

## 30. TCP versus UDP

TCP provides a reliable ordered byte stream with congestion control and connection semantics. UDP provides datagrams without built-in delivery or ordering guarantees and can be useful when the application handles loss or needs low overhead. WebRTC, DNS, streaming, and gaming may use different choices based on latency and reliability needs.

## 31. TCP three-way handshake

The client sends SYN, the server responds with SYN-ACK, and the client sends ACK. This establishes sequence-number agreement and confirms reachability before application data flows.

## 32. HTTP request lifecycle

A client resolves DNS, establishes a connection, negotiates TLS when HTTPS is used, sends an HTTP request through proxies/load balancers, reaches the service, and receives a response. Reuse connections and cache DNS/TLS/session state when appropriate.

## 33. HTTP methods and status codes

GET reads, POST creates or triggers non-idempotent processing, PUT replaces or idempotently writes, PATCH partially updates, and DELETE removes. Status codes should distinguish client validation errors, authentication/authorization failures, missing resources, rate limits, and server failures.

## 34. Idempotency

An operation is idempotent when repeating the same request produces the same intended state. Use an idempotency key stored with the result for payment, order, and job-creation APIs. This protects against client retries and network ambiguity.

## 35. Authentication versus authorization

Authentication identifies the caller; authorization checks what the caller may do or access. Validate authorization on the server for every protected resource. A signed token is not a substitute for checking resource ownership.

## 36. TLS

TLS provides encryption in transit, server authentication through certificates, and integrity. Certificate validation, hostname checks, key rotation, and secure protocol configuration matter; simply using HTTPS does not solve application authorization.

## 37. Load balancers

Layer 4 load balancers route based on network connections. Layer 7 load balancers understand application protocols and can route by host, path, headers, or cookies. Health checks must test meaningful readiness, not merely that a process exists.

## 38. Reverse proxy and forward proxy

A reverse proxy sits in front of servers and provides routing, TLS termination, caching, or security. A forward proxy represents clients accessing external services. The placement changes trust, routing, and policy responsibilities.

## 39. WebSockets, SSE, and polling

- Polling is simple but wastes requests and adds delay.
- SSE provides server-to-client streaming over HTTP and is useful for one-way updates.
- WebSockets provide bidirectional persistent communication but require connection lifecycle, backpressure, and reconnect handling.

## 40. Timeouts, retries, and backoff

Every network call needs a deadline. Retry only transient failures, use bounded exponential backoff with jitter, and make side effects idempotent. Unbounded retries create retry storms and can amplify an outage.

## 41. Rate limiting

Fixed windows are simple but allow boundary bursts. Sliding windows are more accurate. Token buckets allow controlled bursts while limiting average rate. In distributed systems, counters need atomicity, partition behavior, and a defined fail-open/fail-closed policy.

## 42. CDN and caching

A CDN caches content near users and reduces origin load. Cache keys, TTL, invalidation, privacy, stale data, cache stampede, and authorization must be designed explicitly. Never cache tenant-specific data under a shared key.

# Part 4: OOP, design, and code quality

## 43. Encapsulation

Encapsulation hides representation and exposes a stable contract. It allows invariants to be enforced in one place and prevents callers from depending on implementation details.

## 44. Inheritance versus composition

Inheritance expresses an is-a relationship and can create tight coupling. Composition assembles behavior from components and is often easier to test and change. Prefer composition unless substitutability is genuine.

## 45. Polymorphism

Polymorphism allows code to depend on a contract while different implementations provide behavior. It is useful for pricing strategies, storage providers, model providers, and notification channels.

## 46. Dependency injection

Pass dependencies into a component instead of constructing concrete infrastructure inside it. This improves testing, configuration, and replacement of providers.

## 47. Factory, Strategy, Observer, Adapter

- Factory chooses which object to create.
- Strategy swaps an algorithm or policy.
- Observer broadcasts changes to subscribers.
- Adapter converts one interface to another.

Use a pattern when it reduces coupling; do not add patterns solely to appear sophisticated.

## 48. Unit versus integration tests

Unit tests isolate a component and are fast. Integration tests verify real boundaries such as databases, queues, or APIs. Contract tests verify that independent services agree on schemas. A production service needs a balanced test pyramid, not only mocks.

# Part 5: Cloud, APIs, and debugging

## 49. Health checks

Liveness asks whether a process should be restarted. Readiness asks whether it can receive traffic. A readiness check should include required dependencies carefully; otherwise a database outage can cause every instance to restart and worsen the incident.

## 50. Horizontal versus vertical scaling

Vertical scaling increases resources on one machine and is simple but bounded. Horizontal scaling adds instances and improves capacity and availability but requires statelessness, routing, shared storage, coordination, and consistent configuration.

## 51. Observability

Logs describe events, metrics aggregate behavior, and traces connect a request across services. Use correlation IDs, structured fields, latency percentiles, error categories, and safe redaction. Observability should help answer what failed, for whom, when, and why.

## 52. Production debugging method

1. Define user impact and time window.
2. Check recent deployments and dependency health.
3. Compare good and bad requests.
4. Form one falsifiable hypothesis.
5. Add targeted metrics or logs.
6. Mitigate safely with rollback, feature flag, rate limit, or fallback.
7. Verify recovery.
8. Write prevention work and an incident timeline.

## 53. CI/CD

A useful pipeline runs formatting, linting, unit tests, integration tests, security scans, build/package checks, evaluation tests for AI features, and deployment health checks. Promote immutable artifacts and retain rollback versions.

## 54. Secrets and configuration

Do not commit credentials. Use a secret manager, short-lived credentials, least privilege, rotation, environment-specific configuration, and audit logs. Avoid logging tokens or sensitive prompts.

# Part 6: Interview close

End a CS fundamentals answer with a concrete trade-off:

> The simplest correct solution is ____. At larger scale, the bottleneck becomes ____, so I would change ____. The cost of that improvement is ____. I would validate it with ____, and I would monitor ____. 
