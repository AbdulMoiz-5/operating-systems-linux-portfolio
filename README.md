# Operating Systems & Linux Systems Portfolio

A practical portfolio of Linux and operating-systems laboratory work focused on process management, POSIX threads, synchronization, inter-process communication, shell scripting, and Linux kernel configuration.

## Highlights

- Linux filesystem, permissions, process monitoring, Bash automation, and cron
- Process creation and synchronization with `fork()`, `wait()`, `waitpid()`, `getpid()`, and `getppid()`
- POSIX threads, thread attributes, mutexes, condition variables, and thread joins
- Race conditions, file locking, deadlocks, try-lock, producer-consumer, and thread-safe logging
- POSIX semaphores and writer-priority reader-writer synchronization
- IPC concepts including FIFOs, unnamed pipes, `dup()`, and `dup2()`
- Linux kernel 6.1.0 configuration and compilation with NTFS support

## Repository Structure

```text
operating-systems-linux-portfolio/
├── README.md
├── docs/
│   ├── linux-system-administration.md
│   ├── process-management.md
│   ├── inter-process-communication.md
│   ├── concurrency-and-synchronization.md
│   ├── semaphores-and-reader-writer.md
│   └── custom-linux-kernel.md
└── src/
    ├── linux/
    ├── processes/
    ├── threads/
    ├── synchronization/
    ├── semaphores/
    └── ipc/
```

## Tools & Concepts

**Languages:** C, Bash  
**Platforms:** Linux / POSIX  
**APIs & tools:** `pthread`, POSIX semaphores, `fork`, `wait`, `waitpid`, `pipe`, `mkfifo`, `dup`, `dup2`, `flock`, `ps`, `top`, `cron`, GCC, Linux kernel build tools

## Selected Projects

### Process Management

Demonstrations of process creation, parent-child relationships, process IDs, and synchronization using `fork()` and `wait()`/`waitpid()`.

### Concurrency & Synchronization

Examples showing race conditions, mutex protection, deadlock patterns, lock ordering, `pthread_mutex_trylock()`, safe logging, and producer-consumer coordination.

### POSIX Threads

Small thread-based programs covering basic thread creation, passing data to threads, returning results, and thread attributes.

### Semaphores

Producer-consumer and writer-priority reader-writer examples using POSIX semaphores and mutexes.

### Linux Administration & Kernel Work

Command-line administration, resource monitoring, Bash automation, cron scheduling, and a controlled Linux kernel 6.1.0 configuration/build exercise.

## Running the C Examples

Most examples can be compiled with GCC and POSIX threads:

```bash
gcc -Wall -Wextra -pthread source_file.c -o program
./program
```

Semaphore examples may also require the platform's POSIX semaphore support; on modern Linux systems, `-pthread` is normally sufficient.

## Note

The source examples are educational demonstrations derived from operating-systems laboratory work. They are organized as portfolio artifacts and are not presented as production-ready software. Some examples intentionally demonstrate unsafe behavior so the corresponding synchronization technique can be studied.

## Author

Abdul Moiz
