#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static pthread_mutex_t acc1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t acc2 = PTHREAD_MUTEX_INITIALIZER;

static void *transfer_one(void *arg) {
    (void)arg;
    pthread_mutex_lock(&acc1);
    sleep(1);
    pthread_mutex_lock(&acc2);
    puts("Transfer 1 completed");
    pthread_mutex_unlock(&acc2);
    pthread_mutex_unlock(&acc1);
    return NULL;
}

static void *transfer_two(void *arg) {
    (void)arg;
    pthread_mutex_lock(&acc2);
    sleep(1);
    pthread_mutex_lock(&acc1);
    puts("Transfer 2 completed");
    pthread_mutex_unlock(&acc1);
    pthread_mutex_unlock(&acc2);
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, transfer_one, NULL);
    pthread_create(&t2, NULL, transfer_two, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
