#include <pthread.h>
#include <stdio.h>

static int balance = 1000;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void *deposit(void *arg) {
    (void)arg;
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&lock);
        ++balance;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

static void *withdraw(void *arg) {
    (void)arg;
    for (int i = 0; i < 100000; ++i) {
        pthread_mutex_lock(&lock);
        --balance;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Final balance: %d\n", balance);
    pthread_mutex_destroy(&lock);
    return 0;
}
