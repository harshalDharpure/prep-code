# Final Readiness Checklist for London AI / FDE Interviews

## Honest answer

This preparation pack is a strong, high-signal foundation for many London software, AI engineering, applied AI, solutions engineering, and FDE interviews. It is not a guarantee for every role: hiring loops differ by level, team, company, and recruiter-defined interview plan.

You are interview-ready when you can demonstrate the skills below under time pressure, not merely when you have read the question list.

## Gate 1: Coding

Pass standard:

- Solve two medium problems in 70 minutes, including explanation and tests.
- Solve one easy problem in 15 minutes without hints.
- Explain brute force before optimization.
- State the invariant, recurrence, or data-structure reason.
- Handle empty input, duplicates, negative numbers, overflow, invalid input, and boundary indexes.
- Give correct time and space complexity.
- Write code that compiles and can be tested with a small `main()`.

Minimum patterns to master:

- Hash map and prefix sum.
- Two pointers and sliding window.
- Stack and monotonic stack.
- Linked-list fast/slow pointers.
- Tree DFS/BFS.
- Graph DFS/BFS and topological sort.
- Union Find.
- Binary search and binary search on the answer.
- Heap and priority queue.
- Greedy interval scheduling.
- One-dimensional and two-dimensional DP.
- Backtracking.
- Trie and cache design.

## Gate 2: System design

Be able to design and explain:

1. A multi-tenant RAG assistant.
2. A safe tool-using AI agent.
3. A model gateway with routing, rate limits, fallback, and cost controls.
4. A document ingestion and indexing pipeline.
5. An LLM evaluation and regression platform.
6. A webhook or event-processing system with retries and deduplication.
7. A real-time metrics or anomaly-detection service.
8. A globally available API with regional data controls.

For every design, cover:

- Requirements and success metrics.
- Traffic, data size, latency, and availability assumptions.
- API and data model.
- Main components and request flow.
- Storage, queues, caches, and indexing.
- Scaling bottlenecks and partitioning.
- Timeouts, retries, idempotency, backpressure, and dead letters.
- Authentication, authorization, tenant isolation, encryption, and deletion.
- Observability, alerting, rollout, rollback, and disaster recovery.
- Cost, privacy, safety, and quality trade-offs.

## Gate 3: AI engineering

Be ready to explain clearly:

- Embeddings and vector search.
- Chunking and metadata strategy.
- Hybrid retrieval and reranking.
- Precision, recall, MRR, groundedness, and answer quality.
- Offline evaluation versus online evaluation.
- Prompt injection and tool permission boundaries.
- Hallucination reduction and abstention.
- Context-window and token-budget management.
- Batch versus online inference.
- Caching, streaming, latency, throughput, and cost.
- Model routing, fallback models, and versioning.
- PII redaction, retention, auditability, and regional data controls.
- Data drift, feedback loops, and regression detection.

## Gate 4: FDE and customer delivery

Prepare one concrete example for each:

- Turned an ambiguous customer request into requirements.
- Built a working proof of concept quickly.
- Integrated an unreliable or legacy API.
- Debugged a production issue with incomplete information.
- Managed a scope or deadline conflict.
- Explained a technical limitation to a non-technical stakeholder.
- Protected security, privacy, or safety despite delivery pressure.
- Converted a prototype into a maintainable production system.
- Worked across engineering, product, sales, and customer teams.
- Measured business impact after launch.

Your examples should include numbers where possible: latency, cost, adoption, revenue, accuracy, incident duration, throughput, or time saved.

## Gate 5: Behavioral and communication

Prepare concise STAR stories for:

- Ownership.
- Conflict and disagreement.
- Failure and learning.
- Production incident.
- Ambiguous requirements.
- Customer escalation.
- Influence without authority.
- Fast learning.
- Security or ethical judgment.
- Biggest technical impact.

Practice explaining a design twice: once to an engineer and once to a customer executive.

## Role-specific focus

### Product Software Engineer

Prioritize coding, data structures, algorithms, debugging, system design, testing, and behavioral impact.

### Applied AI / ML Engineer

Add Python, data processing, ML fundamentals, evaluation, inference, retrieval, experimentation, and production observability.

### FDE / Solutions / Forward-Deployed Engineer

Add API integration, SQL, customer discovery, rapid prototyping, deployment, incident handling, documentation, and stakeholder communication.

### AI Infrastructure Engineer

Add concurrency, memory, networking, distributed systems, performance profiling, queues, storage, and model serving.

## Final 14-day drill

### Days 1-4: Core coding

Solve 3 timed problems daily: hashing/sliding window, trees/graphs, and DP/greedy. Review every failed edge case.

### Days 5-7: Advanced coding and design

Solve one hard coding problem daily and complete two 45-minute system designs.

### Days 8-10: AI production

Design RAG, an LLM gateway, and an evaluation platform. Include security, cost, latency, and failure recovery.

### Days 11-12: FDE simulation

Complete one API/debugging exercise and one customer-facing technical presentation each day.

### Days 13-14: Full mock loop

Do a coding interview, system design interview, AI deep dive, behavioral interview, and final review of weak patterns.

## Final decision rule

Do not mark yourself ready because you recognized the solution. Mark yourself ready when you can solve, test, explain, and defend the trade-offs without notes.

Before scheduling the interview, ask the recruiter about the exact language, number of coding rounds, system-design expectations, SQL/debugging scope, take-home work, customer presentation, travel, language, and relocation requirements.
