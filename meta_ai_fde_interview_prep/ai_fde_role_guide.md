# AI Engineering and FDE Role Guide

## What interviewers usually test

1. Can you solve a coding problem correctly and explain the invariant?
2. Can you turn an ambiguous customer problem into a measurable technical plan?
3. Can you integrate APIs and data sources safely in an imperfect environment?
4. Can you design an AI workflow that is useful, observable, affordable, and safe?
5. Can you debug production behavior rather than only write greenfield code?
6. Can you communicate trade-offs to engineers, customers, and executives?

## Coding expectations

For each problem:

- Restate the problem and ask about constraints.
- Give a simple baseline before optimizing.
- State the invariant or recurrence.
- Use meaningful names and small helper functions.
- Test empty input, one element, duplicates, negative values, overflow, and invalid data.
- State time and space complexity.
- Mention what you would monitor or log in production when relevant.

## AI engineering topics

### LLM application architecture

- Request gateway, authentication, rate limiting, model router, prompt templates.
- Retrieval pipeline: ingestion, chunking, metadata, embeddings, vector search, reranking.
- Generation controls: context limits, structured output, tool calls, retries, fallbacks.
- Evaluation: golden sets, human review, exact match, precision/recall, groundedness, latency, cost.
- Operations: tracing, prompt/model versioning, cache strategy, redaction, audit logs.

### Reliability and safety

- Timeouts, retries with jitter, circuit breakers, idempotency, dead-letter queues.
- Prompt injection, sensitive-data leakage, excessive permissions, untrusted tool output.
- PII handling, retention, regional deployment, access control, tenant isolation.
- Hallucination handling: citations, abstention, validation, human escalation.

### Data and ML basics

- Train/validation/test leakage.
- Class imbalance, precision/recall, ROC-AUC, calibration.
- Embeddings, cosine similarity, nearest-neighbor search.
- Batch versus online inference.
- Feature freshness, drift, feedback loops, and offline/online skew.

## FDE-specific exercises

Practice explaining how you would:

1. Integrate a customer CRM with an AI assistant while preserving permissions.
2. Migrate a batch workflow to an event-driven pipeline with replay support.
3. Investigate why an AI answer became slower and less accurate after a release.
4. Build a proof of concept in two weeks without creating an unmaintainable system.
5. Handle a customer request that conflicts with privacy or safety requirements.
6. Design a multi-tenant retrieval service with per-tenant deletion.
7. Debug a webhook integration that occasionally duplicates orders.
8. Create an evaluation harness for a support-ticket summarizer.
9. Explain a production incident to a non-technical customer.
10. Decide whether to use a hosted model, open-source model, or a hybrid.

## System design prompts

- Design a production RAG assistant for enterprise documents.
- Design a multi-tenant LLM gateway.
- Design an AI agent that calls business tools safely.
- Design a real-time fraud or abuse detection service.
- Design a feature flag and prompt configuration service.
- Design an evaluation and regression platform for LLM applications.
- Design a notification service with rate limits and retries.
- Design a document ingestion and indexing pipeline.
- Design a customer-facing analytics dashboard with fresh metrics.
- Design a globally available API with regional data controls.

## Behavioral stories to prepare

Use the STAR structure with measurable results:

- A difficult customer or stakeholder alignment problem.
- A production incident and the permanent fix.
- A project delivered with unclear requirements.
- A technical disagreement and how you resolved it.
- A migration or integration with legacy systems.
- A time you reduced latency, cost, or operational load.
- A failure, what you learned, and what changed afterward.
- A situation where you protected security, privacy, or reliability.
- A fast prototype that became a maintainable product.
- A time you influenced without formal authority.

## Compact answer template

- Goal: who needs what and why?
- Constraints: scale, latency, privacy, cost, reliability, deadline.
- Baseline: simplest viable implementation.
- Design: components and data flow.
- Failure modes: what breaks and how the system recovers.
- Validation: tests, metrics, rollout, and success criteria.
- Trade-off: what you deliberately did not optimize yet.
