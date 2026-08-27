# POSIX Thread Operations and Attributes

The thread examples in `src/threads/` cover basic thread creation, passing data to worker functions, returning results through shared structures, and configuring thread attributes such as stack size and scheduling policy.

The scheduling-policy example demonstrates configuration only. On Linux, applying real-time policies such as `SCHED_FIFO` can require appropriate privileges, so failure to apply that policy should be treated as an environment/permission issue rather than assumed success.
