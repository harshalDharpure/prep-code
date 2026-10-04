# Start Here: AI / ML / LLM / FDE Preparation Path

## The correct order

Do not begin with advanced agents, distributed training, or every framework. Build the foundation in layers and create proof of work as you progress.

## Phase 0: Baseline assessment

Time: 1 day

1. Solve Two Sum, Longest Substring Without Repeating Characters, Binary Tree Level Order Traversal, Number of Islands, and House Robber without notes.
2. Explain each solution aloud and write time and space complexity.
3. Write down weak areas instead of restarting the whole curriculum.
4. Confirm whether your target roles require Python, C++, SQL, system design, ML, or customer presentations.

Use:

- [meta_focused_interview_plan.md](meta_focused_interview_plan.md)
- [final_readiness_checklist.md](final_readiness_checklist.md)

## Phase 1: Programming foundation

Time: Weeks 1-2

Primary language: Python for AI roles. Keep C++ practice if the target interview allows or requires it.

Study in this order:

1. Arrays, strings, hash maps, and sets.
2. Two pointers and sliding windows.
3. Stacks, queues, and heaps.
4. Linked lists.
5. Trees and recursion.
6. Graph BFS/DFS and topological sort.
7. Binary search and intervals.
8. Greedy algorithms and basic dynamic programming.

Daily routine:

- 20 minutes: learn one pattern.
- 40 minutes: solve one problem without looking.
- 20 minutes: review an optimal solution and edge cases.
- 20 minutes: re-code from a blank file and explain aloud.

Target: 25-35 problems solved properly, not 100 problems copied.

Use:

- [coding_question_bank.md](coding_question_bank.md)
- [top_50_coding_solutions.cpp](top_50_coding_solutions.cpp)
- [interview_explanations_and_answer_scripts.md](interview_explanations_and_answer_scripts.md)

## Phase 2: Python, SQL, and engineering basics

Time: Week 3

Learn:

- Python functions, classes, typing, exceptions, testing, logging, and async basics.
- SQL joins, grouping, CTEs, window functions, deduplication, rolling metrics, and query plans.
- HTTP, REST, authentication, JSON, webhooks, retries, idempotency, and pagination.
- Git, Linux commands, Docker, environment variables, and basic CI.

Build one small service:

- a FastAPI endpoint,
- input validation,
- a database or file-backed store,
- unit tests,
- structured logs,
- Docker setup,
- and a README explaining how to run it.

## Phase 3: ML fundamentals

Time: Week 4

Study:

1. Supervised and unsupervised learning.
2. Train/validation/test split and leakage.
3. Bias, variance, overfitting, and regularization.
4. Classification and regression metrics.
5. Precision, recall, F1, ROC-AUC, PR-AUC, and calibration.
6. Class imbalance and threshold selection.
7. Feature engineering and data quality.
8. Drift, experimentation, and error analysis.

Build one small ML project with:

- a clear business problem,
- a baseline model,
- a data split explanation,
- metrics chosen for the business cost,
- error analysis,
- and a short model card.

Use:

- [ai_roles_high_frequency_master_sheet.md](ai_roles_high_frequency_master_sheet.md), Parts 2 and 3.
- [meta_complete_preparation_master.md](meta_complete_preparation_master.md), ML section.

## Phase 4: LLM and GenAI foundations

Time: Weeks 5-6

Study in this order:

1. Tokens, embeddings, context windows, and transformer intuition.
2. Prompt design and structured outputs.
3. RAG: ingestion, chunking, metadata, embeddings, retrieval, reranking, and citations.
4. Evaluation: retrieval recall, MRR, groundedness, answer quality, latency, and cost.
5. Fine-tuning versus RAG versus deterministic workflows.
6. Tool calling, agents, state, budgets, and loop prevention.
7. Prompt injection, PII, tenant isolation, and safe tool permissions.
8. Streaming, caching, retries, fallbacks, and model routing.

Do not build a plain chatbot and stop. Build an evaluation-backed system.

## Phase 5: First portfolio project

Time: Weeks 6-8

Build: **Production-style multi-tenant RAG assistant**

Minimum features:

- document ingestion,
- chunking with metadata,
- hybrid or vector retrieval,
- tenant/document permissions,
- citations,
- structured response validation,
- evaluation dataset,
- latency and cost logging,
- prompt/model versioning,
- rate limiting,
- Docker deployment,
- tests and CI.

Publish:

- architecture diagram,
- README with setup steps,
- baseline versus improved evaluation,
- threat model,
- load-test results,
- known limitations,
- two-minute demo.

Use:

- [international_ai_job_targeting_and_interview_sheet.md](international_ai_job_targeting_and_interview_sheet.md), Project A.
- [interview_explanations_and_answer_scripts.md](interview_explanations_and_answer_scripts.md), RAG design section.

## Phase 6: Production AI engineering

Time: Weeks 9-10

Learn and implement:

- queues and workers,
- retries with exponential backoff and jitter,
- idempotency,
- circuit breakers,
- token-bucket rate limiting,
- caching and TTL,
- observability and tracing,
- CI/CD,
- cloud deployment basics,
- Kubernetes concepts,
- secrets and access control,
- rollback and incident response.

Build one reusable component such as a rate limiter, evaluation runner, or model router. Add tests and a design document.

## Phase 7: System design and FDE preparation

Time: Weeks 11-12

Practice one 45-minute design every two days:

1. Enterprise RAG assistant.
2. Multi-tenant LLM gateway.
3. Safe tool-using agent.
4. LLM evaluation platform.
5. Document ingestion pipeline.
6. AI support-ticket summarizer.
7. SOC AI copilot.
8. Notification service with retries.
9. Real-time abuse detection.
10. Globally available API with regional data controls.

For each design, cover:

- requirements,
- scale assumptions,
- API and data model,
- data flow,
- storage and queues,
- authorization,
- failure modes,
- evaluation,
- observability,
- cost,
- rollout and rollback.

Prepare ten STAR stories for ownership, failure, conflict, customer delivery, incident response, ambiguity, security, learning, influence, and measurable impact.

## Phase 8: Interview practice and applications

Start applications when you have:

- one strong project that can be explained deeply,
- 30-40 coding problems understood and re-coded,
- basic SQL and API confidence,
- three system designs practiced,
- ten behavioral stories,
- and a tailored CV.

Do not wait until you know every topic. Apply while continuing to improve.

Application package:

- one-page role-targeted CV,
- GitHub project with clear README,
- architecture diagram,
- evaluation report,
- short technical article,
- concise project explanation,
- location, work authorization, relocation, and travel details.

## Weekly schedule template

### Monday to Friday

- Coding: 60 minutes.
- AI/ML study: 60 minutes.
- Project implementation: 90 minutes.
- Explanation practice: 20 minutes.

### Saturday

- One timed coding mock.
- One system-design mock.
- Project cleanup, tests, and documentation.

### Sunday

- Review mistakes.
- Re-solve failed problems.
- Update notes and CV evidence.
- Rest enough to maintain consistency.

## What to postpone

Do not start with:

- training a frontier model from scratch,
- learning every agent framework,
- collecting certificates without projects,
- solving hundreds of random problems,
- memorizing definitions without examples,
- building a beautiful UI without evaluation or reliability.

## Your first seven days

### Day 1

Baseline coding assessment and target-role selection.

### Day 2

Hash maps, arrays, Two Sum, Subarray Sum Equals K.

### Day 3

Sliding window, longest substring, minimum window concept.

### Day 4

Stacks, queues, heaps, and one monotonic-stack problem.

### Day 5

Trees, BFS, DFS, and one LCA problem.

### Day 6

Python API basics, JSON validation, tests, and logging.

### Day 7

Explain RAG on paper and design the first portfolio project.

## The rule that matters most

Every topic must produce one of these:

- working code,
- a measured experiment,
- a design document,
- a test,
- a diagram,
- or a clear explanation recorded in your own words.

That is how preparation becomes evidence of engineering ability.
