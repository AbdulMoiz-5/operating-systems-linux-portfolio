# POSIX Semaphores and Reader-Writer Synchronization

## Overview

This project studies POSIX semaphores as synchronization primitives and applies them to two classic operating-systems problems: the bounded-buffer producer-consumer problem and the writer-priority reader-writer problem.

## Bounded Buffer

The producer-consumer example uses counting semaphores to track available and occupied buffer slots, while a mutex protects shared buffer indexes. Multiple producers generate items and multiple consumers remove them.

Key ideas:

- `sem_wait()` blocks when the required resource is unavailable.
- `sem_post()` signals that a resource has become available.
- A mutex protects the shared circular buffer from concurrent modification.
- A separate completion counter prevents consumers from running beyond the intended workload.

## Writer-Priority Reader-Writer

The reader-writer example allows multiple readers to access shared data concurrently, while writers receive exclusive access. A gate semaphore prevents new readers from entering when writers are waiting, reducing writer starvation.

The model uses:

- a semaphore controlling writer access;
- a semaphore acting as a reader-entry gate;
- mutexes protecting reader/writer counters and completion state.

## Learning Outcome

These examples demonstrate how operating systems coordinate concurrent execution when several threads share limited resources or shared data. They also show why synchronization requires both mutual exclusion and correct lifecycle/termination logic.
