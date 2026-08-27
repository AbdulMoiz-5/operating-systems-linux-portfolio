#!/usr/bin/env bash
# Demonstration of a lock-order inversion that can lead to deadlock.
# Use two separate terminals in a disposable directory.

# Terminal 1:
# flock file1 -c "sleep 5 && flock file2 -c 'echo done from T1'"
#
# Terminal 2:
# flock file2 -c "sleep 5 && flock file1 -c 'echo done from T2'"
#
# Inspect the state with:
# ps aux | grep flock
