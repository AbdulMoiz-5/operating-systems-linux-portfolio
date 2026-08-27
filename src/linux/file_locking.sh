#!/usr/bin/env bash
# Demonstration of protecting a shared counter with flock.

set -u
counter_file="counter.txt"
echo 0 > "$counter_file"

worker() {
    for ((i=1; i<=1000; i++)); do
        flock "$counter_file" -c '
            value=$(cat counter.txt)
            value=$((value + 1))
            echo "$value" > counter.txt
        '
    done
}

worker &
worker &
wait

printf 'Final value with locking: '
cat "$counter_file"
