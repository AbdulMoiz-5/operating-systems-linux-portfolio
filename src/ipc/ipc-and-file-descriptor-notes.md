# IPC and File Descriptors

This folder's main written case study is in `docs/inter-process-communication.md`.

Key system calls from the laboratory work:

- `pipe()` — creates an unnamed pipe between related processes.
- `mkfifo()` — creates a named pipe in the filesystem.
- `unlink()` — removes a named FIFO after use.
- `dup()` — duplicates a file descriptor.
- `dup2()` — duplicates a descriptor into a chosen descriptor number, making it useful for stdin/stdout/stderr redirection.

These primitives are the building blocks behind many Unix pipelines and process-communication patterns.
