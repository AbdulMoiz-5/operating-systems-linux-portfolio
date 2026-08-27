#include <pthread.h>
#include <stdio.h>
#include <time.h>

static pthread_mutex_t m1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t m2 = PTHREAD_MUTEX_INITIALIZER;

static void *worker(void *arg) {
    long id = (long)arg;

    for (;;) {
        if (pthread_mutex_trylock(&m1) == 0) {
            if (pthread_mutex_trylock(&m2) == 0) {
                printf("Thread %ld acquired both locks\n", id);
                pthread_mutex_unlock(&m2);
                pthread_mutex_unlock(&m1);
                break;
            }
            pthread_mutex_unlock(&m1);
        }
        struct timespec ts = {0, 1000000};
        nanosleep(&ts, NULL);
    }
    return NULL;
}

int main(void) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, worker, (void *)1);
    pthread_create(&t2, NULL, worker, (void *)2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    puts("No deadlock occurred.");
    return 0;
}
