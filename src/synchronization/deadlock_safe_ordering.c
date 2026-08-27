#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t acc1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t acc2 = PTHREAD_MUTEX_INITIALIZER;

static void *safe_transfer(void *arg) {
    long id = (long)arg;

    /* Always acquire multiple locks in the same order. */
    pthread_mutex_lock(&acc1);
    pthread_mutex_lock(&acc2);

    printf("Thread %ld: transfer completed safely\n", id);

    pthread_mutex_unlock(&acc2);
    pthread_mutex_unlock(&acc1);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, safe_transfer, (void *)1);
    pthread_create(&t2, NULL, safe_transfer, (void *)2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_mutex_destroy(&acc1);
    pthread_mutex_destroy(&acc2);
    puts("All transfers completed without deadlock.");
    return 0;
}
