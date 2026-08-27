#include <pthread.h>
#include <sched.h>
#include <stdio.h>

static void *show_thread(void *arg) {
    (void)arg;
    printf("Thread ID: %lu\n", (unsigned long)pthread_self());
    return NULL;
}

int main(void) {
    pthread_t thread;
    pthread_attr_t attr;
    size_t stack_size = 2U * 1024U * 1024U;
    int policy;

    if (pthread_attr_init(&attr) != 0) {
        return 1;
    }

    if (pthread_attr_setstacksize(&attr, stack_size) != 0) {
        pthread_attr_destroy(&attr);
        return 1;
    }

    /* Demonstrates configuring an attribute; scheduling-policy permissions
       may prevent the requested policy from being applied at thread creation. */
    pthread_attr_setschedpolicy(&attr, SCHED_FIFO);

    if (pthread_create(&thread, &attr, show_thread, NULL) != 0) {
        pthread_attr_destroy(&attr);
        return 1;
    }

    pthread_attr_getstacksize(&attr, &stack_size);
    pthread_attr_getschedpolicy(&attr, &policy);

    printf("Configured stack size: %zu bytes\n", stack_size);
    if (policy == SCHED_FIFO) {
        printf("Configured policy: SCHED_FIFO\n");
    } else if (policy == SCHED_RR) {
        printf("Configured policy: SCHED_RR\n");
    } else {
        printf("Configured policy: SCHED_OTHER\n");
    }

    pthread_join(thread, NULL);
    pthread_attr_destroy(&attr);
    return 0;
}
