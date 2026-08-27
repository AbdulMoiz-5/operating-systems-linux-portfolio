# Inter-Process Communication with Pipes and File Descriptors

## Overview

This project studies Unix/Linux pipes and file-descriptor duplication as mechanisms for moving data between processes and redirecting standard streams.

## Topics Covered

- Named pipes (FIFOs) with `mkfifo()` and cleanup with `unlink()`
- Unnamed pipes with `pipe()` for related processes
- Blocking and non-blocking pipe behavior
- Multiple producers and a single consumer
- Parent-child stream communication
- `dup()` and `dup2()` for file-descriptor duplication
- Redirecting standard input, output, and error
- Combining pipes with descriptor redirection

## Key Learning

A pipe provides a controlled data channel between processes. `dup2()` is especially useful for shell-style redirection because it can replace a standard descriptor such as stdin or stdout with a pipe or file.

## Portfolio Value

The project demonstrates practical knowledge of Unix IPC and the file-descriptor model that underlies pipelines and many command-line tools.
