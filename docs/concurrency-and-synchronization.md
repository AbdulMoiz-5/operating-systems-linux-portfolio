# Concurrency and Synchronization

## Overview

This project demonstrates common concurrency problems and synchronization techniques using POSIX threads and Linux processes.

## Topics Covered

- CPU-bound process scheduling
- Race conditions on shared files
- File locking with `flock`
- Busy waiting and CPU consumption
- POSIX mutexes
- Deadlock creation and prevention
- `pthread_mutex_trylock()`
- Thread-safe file logging
- Producer-consumer synchronization with condition variables
- Binary and counting semaphore concepts
- Reader-writer synchronization

## Design Lessons

### Race Conditions

When multiple workers read and modify shared state without synchronization, the final result can depend on execution timing. This makes concurrent programs unpredictable.

### Mutexes

A mutex protects a critical section so that only one thread accesses a protected resource at a time.

### Deadlocks

The examples demonstrate how inconsistent lock ordering can create a circular wait. A simple prevention strategy is to acquire multiple locks in a consistent global order.

### Try-Lock

`pthread_mutex_trylock()` allows a thread to attempt a lock without waiting indefinitely. Releasing an already-held lock when the second lock cannot be obtained avoids holding resources while waiting.

### Producer-Consumer

Condition variables coordinate producers and consumers so that producers wait when the buffer is full and consumers wait when it is empty.

## Portfolio Value

Concurrency is a core operating-systems topic and also appears in real servers, databases, and security-sensitive software. These examples show both the failure modes and the synchronization techniques used to address them.
