# LLD and HLD Interview Answers

## How to answer any design question

Start with:

> I will clarify the scope and constraints first, define the core entities and APIs, explain the main flow, and then cover persistence, concurrency, failure handling, scalability, security, observability, and trade-offs.

Always ask:

- Who are the users?
- What are the core actions?
- What is explicitly out of scope?
- Expected traffic and data size?
- Latency, availability, consistency, and durability needs?
- Security, privacy, and compliance constraints?
- Is this a machine-coding/LLD or distributed-system/HLD question?

# Part 1: LLD answer framework

## LLD sequence

1. Clarify requirements.
2. Identify entities and responsibilities.
3. Define relationships and state transitions.
4. Define interfaces and public methods.
5. Apply SOLID only where it helps changeability.
6. Choose data structures and persistence boundaries.
7. Explain error handling and concurrency.
8. Write clean code with tests.
9. Discuss one extension and one trade-off.

## SOLID in interview language

- Single Responsibility: one reason to change.
- Open/Closed: add behavior through extension rather than editing stable code.
- Liskov Substitution: subtypes preserve the parent contract.
- Interface Segregation: clients should not depend on methods they do not use.
- Dependency Inversion: high-level policy depends on abstractions, not concrete infrastructure.

Do not force a design pattern. Start with responsibilities and introduce a pattern only when it removes real coupling.

# Part 2: LLD designs

## 1. Parking lot

### Requirements

Park cars, motorcycles, and trucks; allocate compatible spots; issue tickets; calculate payment; release spots; support multiple floors.

### Entities

- `Vehicle`: id, type, registration.
- `ParkingSpot`: id, type, state, current vehicle.
- `ParkingFloor`: collection of spots.
- `ParkingLot`: floors and allocation policy.
- `Ticket`: vehicle, spot, entry time, status.
- `PricingStrategy`: calculates price.
- `Payment`: method, amount, status.
- `SpotAllocationStrategy`: chooses a compatible free spot.

### APIs

- `issueTicket(vehicle)`
- `findAvailableSpot(vehicleType)`
- `releaseSpot(ticket)`
- `calculatePrice(ticket, exitTime)`
- `processPayment(ticket, paymentMethod)`

### Design answer

Use composition: the parking lot owns floors, floors own spots, and strategies decide allocation and pricing. Avoid a large switch statement inside `ParkingLot`. Use interfaces for allocation and pricing so rules can change independently.

### Hard parts

- Two vehicles cannot acquire the same spot.
- Payment failure must not silently release the spot.
- Repeated exit requests must be idempotent.
- Lost tickets require a defined policy.
- Spot state should survive process restart if the system is durable.

### Tests

- Compatible and incompatible vehicle.
- Full lot.
- Concurrent allocation.
- Duplicate payment request.
- Payment failure.
- Lost ticket.

## 2. Vending machine

### Entities

`Product`, `Slot`, `Inventory`, `Money`, `PaymentProcessor`, `VendingMachineState`.

### States

Idle, product selected, payment pending, dispensing, refunding, out of service.

### Design answer

Use the State pattern because allowed operations change by state. A payment processor abstraction supports cash, card, and digital wallet. Dispensing must be transactional: either inventory decrements and the product is delivered, or the payment is refunded and inventory remains unchanged.

### Failure cases

- Insufficient payment.
- Product unavailable.
- Payment accepted but dispensing fails.
- Power loss during a transaction.

## 3. Logging framework

### Requirements

Levels, structured fields, multiple sinks, filtering, asynchronous output, rotation, and safe shutdown.

### Design answer

Expose a small logger interface. Build log events with timestamp, level, message, trace id, service, and structured fields. Use a bounded queue for asynchronous sinks. If the queue is full, define whether to block, sample, drop low-priority logs, or fail open.

### Production concerns

- Redact secrets and PII.
- Never block critical request paths indefinitely.
- Preserve ordering only where required.
- Flush on shutdown.
- Add metrics for dropped logs and sink failures.

## 4. LRU cache

### Requirements

Expected O(1) get and put, capacity limit, eviction of least recently used item.

### Design answer

Use a hash map from key to a doubly linked-list node. The list is ordered from most recent to least recent. On get or update, move the node to the front. On capacity overflow, remove the tail.

### Invariant

Every map entry points to exactly one list node, and list order exactly matches recency order.

### Extensions

TTL, thread safety, size-based values, statistics, sharding, and distributed cache behavior.

## 5. Pub/sub system

### LLD components

Publisher, topic, subscription, consumer, message, broker, offset, retry policy.

### Design answer

Keep publisher and consumer decoupled through topics. Consumers acknowledge messages and store offsets. At-least-once delivery is practical, so consumers must be idempotent. Add dead-letter handling for repeated failures.

### Questions to discuss

- Ordering: global, per topic, or per key?
- Delivery: at-most-once, at-least-once, or effectively-once?
- Backpressure and slow consumers?
- Replay and retention?
- Consumer group behavior?

## 6. Task scheduler

### Design answer

Represent a task with id, payload, priority, dependencies, retry policy, deadline, and status. Use a priority queue for ready tasks and a dependency graph for blocked tasks. Persist state transitions and use leases so a crashed worker’s task can be retried.

### Correctness

A task should not execute twice unless the operation is idempotent or protected by a lease/idempotency key.

# Part 3: HLD answer framework

## HLD sequence

1. Requirements and non-goals.
2. Scale estimates.
3. API and data model.
4. High-level components.
5. Main read and write flow.
6. Storage, indexes, cache, and queues.
7. Partitioning and replication.
8. Reliability and failure recovery.
9. Security and privacy.
10. Observability and SLOs.
11. Deployment and migration.
12. Bottleneck and trade-off.

## Scale estimate template

State assumptions:

- Daily active users.
- Requests per user.
- Peak multiplier.
- Average request and response size.
- Retention period.
- Read/write ratio.

Then derive approximate requests per second, storage per day, and bandwidth. Exact arithmetic is less important than showing how the estimate drives architecture.

# Part 4: HLD designs

## 1. URL shortener

### API

- `POST /short-links`
- `GET /{code}`
- `GET /short-links/{id}/analytics`

### Components

API gateway, ID generator, metadata store, cache, redirect service, analytics event stream, aggregation store.

### Design

Generate a collision-safe code using a sequence, random id with uniqueness check, or encoded distributed id. Cache hot redirects. Send analytics asynchronously so redirects stay fast.

### Trade-offs

- Strong uniqueness versus simple generation.
- Cache freshness versus redirect latency.
- Synchronous analytics accuracy versus availability.

## 2. News feed

### Requirements

Create posts, follow users, read personalized feed, support high read volume and acceptable freshness.

### Design choices

Fanout-on-write is fast for reads but expensive for celebrity accounts. Fanout-on-read reduces write amplification but increases read latency. A hybrid approach uses precomputed feeds for ordinary users and dynamic merge for high-fanout accounts.

### Components

Post service, graph service, feed store, ranking service, cache, event stream, moderation pipeline.

### Metrics

Feed latency, freshness, ranking engagement, write amplification, cache hit rate, and moderation delay.

## 3. Chat system

### Components

Gateway, connection service, conversation service, message store, fanout service, delivery queue, notification service, presence store, media storage.

### Key decisions

- Per-conversation ordering key.
- Durable message id and idempotency.
- Delivery states: sent, delivered, read.
- Offline queue and reconnect behavior.
- WebSocket for live delivery with push fallback.

### Failure handling

Persist before acknowledgement, deduplicate client retries, replay missed messages from a cursor, and isolate notification failure from message durability.

## 4. Ticket or seat booking

### Core problem

Prevent double booking during contention.

### Design

Use a seat state machine and an expiring reservation. A transaction or conditional write changes available to held only if the version/state matches. Payment confirmation changes held to sold. Expired holds return to available.

### Must discuss

- Reservation TTL.
- Idempotency.
- Payment timeout.
- Clock and expiry handling.
- Overselling prevention.
- Reconciliation after external payment success but internal timeout.

## 5. Ride sharing

### Components

Trip service, driver location stream, geospatial index, matching service, pricing service, payment service, notification service, event store.

### Design

Partition location by geographic cells and update driver availability through a stream. Match using distance, ETA, vehicle type, and fairness. Use a trip state machine and idempotent payment events.

### Hard parts

Stale locations, driver race conditions, cancellation, surge recalculation, network loss, and privacy of location data.

## 6. Distributed rate limiter

### Requirements

Limit by user, tenant, IP, API, or token budget across many instances.

### Algorithms

- Fixed window: simple but boundary bursts.
- Sliding log: accurate but memory-heavy.
- Sliding counter: approximate and efficient.
- Token bucket: supports controlled bursts.
- Leaky bucket: smooths output.

### Distributed design

Use a centralized atomic store or co-located regional counters. Define behavior when the store is unavailable: fail open for low-risk reads or fail closed for sensitive operations. Add clock and replication considerations.

## 7. Object storage / drive

### Components

Metadata service, object store, upload service, download gateway, permissions service, metadata database, event pipeline, virus scanner, search index.

### Design

Upload in chunks with resumable sessions. Store metadata transactionally and large objects in blob storage. Use content hashes for deduplication only when authorization and retention rules permit it.

### Hard parts

Multipart upload recovery, sharing permissions, deletion semantics, versioning, malware scanning, and eventual search indexing.

## 8. Web crawler

### Components

URL frontier, scheduler, fetch workers, robots policy, parser, deduplication store, content store, indexing pipeline.

### Design

Partition by host to enforce politeness and per-host concurrency. Deduplicate URLs and content. Retry transient failures with backoff. Respect robots and legal constraints.

### Metrics

Fetch success, freshness, duplicate rate, host error rate, queue age, and indexing delay.

## 9. LLM gateway

### Components

Authentication, tenant quota, model router, prompt registry, request queue, provider adapters, fallback policy, response validator, tracer, cost ledger.

### Design

Route by capability, latency, privacy, region, and cost. Enforce token budgets before provider calls. Add provider-specific timeout and retry policy. Validate structured output and emit safe traces.

### Critical trade-off

A cheaper fallback may have different quality, tool behavior, safety, and data-residency properties. Fallback must be evaluated, not assumed equivalent.

## 10. Enterprise RAG

### Flow

Connector -> parser -> chunker -> metadata/ACL -> embedding and keyword indexes -> permission-filtered retrieval -> reranking -> bounded context -> model -> citations and validation.

### SLOs

Retrieval recall, groundedness, citation correctness, p95 time to first token, p95 completion latency, cost per successful answer, and unauthorized retrieval rate.

### Security

Enforce tenant and document authorization before generation. Treat documents as untrusted content to resist indirect prompt injection.

## 11. LLM evaluation platform

### Components

Dataset registry, prompt/model registry, batch runner, evaluator service, human review UI, metrics store, slice analyzer, regression gate, report generator.

### Design

Version data, prompts, models, retrieval configuration, and evaluator rules together. Compare every candidate with a baseline. Block rollout when quality, safety, latency, or cost guardrails regress.

## 12. SOC AI copilot

### Components

Alert ingestion, incident store, retrieval over playbooks, model gateway, read-only investigation tools, analyst approval UI, audit log, evaluation pipeline.

### Safety

Logs and threat reports are untrusted input. Use least-privilege tools, validate commands, require confirmation for containment or deletion, and evaluate missed incidents as well as time saved.

# Part 5: HLD trade-off vocabulary

Use precise trade-offs:

- Strong consistency versus availability.
- Freshness versus cost.
- Read latency versus write amplification.
- Simplicity versus extensibility.
- Exactness versus operational scale.
- Synchronous certainty versus asynchronous throughput.
- Central coordination versus regional autonomy.
- Model quality versus latency and cost.
- Recall versus precision.
- Automation versus human control.
- Privacy versus observability detail.

# Part 6: Design answer ending

End with:

> The main bottleneck is ____. I would address it first with ____. The main failure mode is ____, so I would add ____. I am intentionally trading ____ for ____, because the stated priority is ____. With more time, I would validate the design using load tests, fault injection, and a staged rollout.
