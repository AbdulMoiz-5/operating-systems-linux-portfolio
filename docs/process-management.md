# Process Management with fork() and wait()

## Overview

This project explores Unix/Linux process creation and synchronization using the process-management system calls `fork()`, `wait()`, `waitpid()`, `getpid()`, and `getppid()`.

## Concepts Covered

- Creating child processes with `fork()`
- Parent/child relationships and process trees
- Process identifiers using `getpid()` and `getppid()`
- Copy-on-write behavior after `fork()`
- Waiting for child processes to finish
- Sequential and parallel child-process creation
- Handling command-line arguments

## Key Learning

`fork()` creates a new process by duplicating the calling process's execution context. The parent and child then continue independently. Synchronization with `wait()` or `waitpid()` allows the parent to control when it continues, which is important when the order of operations matters.

## Portfolio Value

The project demonstrates a foundational understanding of how Linux creates, identifies, and synchronizes processes.
