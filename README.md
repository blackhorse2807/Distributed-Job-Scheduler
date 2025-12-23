## Distributed Job Scheduler (C++)

A moderately advanced low-level design project implementing a background job scheduler.
The system supports job lifecycle management, retries with backoff, worker execution,
and thread-safe job storage.

### Features
- Job lifecycle state machine
- Retry strategy using Strategy Pattern
- Thread-safe in-memory repository
- Scheduler-worker separation
- Failure handling and dead jobs

### Concepts Used
- OOP & SOLID principles
- Design patterns (Strategy)
- Concurrency (mutex)
- Backend system design fundamentals
