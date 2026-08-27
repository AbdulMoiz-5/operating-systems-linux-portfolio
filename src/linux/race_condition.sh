#!/usr/bin/env bash
# Demonstration of a race condition on a shared counter file.
# Run this script from a disposable directory.

set -u

counter_file="counter.txt"
echo 0 > "$counter_file"

worker() {
    for ((i=1; i<=1000; i++)); do
        value=$(cat "$counter_file")
        sleep 0.001
        value=$((value + 1))
        echo "$value" > "$counter_file"
    done
}

worker &
worker &
wait

printf 'Final value without locking: '
cat "$counter_file"
