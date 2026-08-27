#include <pthread.h>
#include <stdio.h>

#define BUFFER_SIZE 5
#define ITEMS 10

static int buffer[BUFFER_SIZE];
static int count;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t not_full = PTHREAD_COND_INITIALIZER;
static pthread_cond_t not_empty = PTHREAD_COND_INITIALIZER;

static void *producer(void *arg) {
    (void)arg;
    for (int i = 0; i < ITEMS; ++i) {
        pthread_mutex_lock(&lock);
        while (count == BUFFER_SIZE)
            pthread_cond_wait(&not_full, &lock);

        buffer[count++] = i;
        printf("Produced: %d\n", i);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

static void *consumer(void *arg) {
    (void)arg;
    for (int i = 0; i < ITEMS; ++i) {
        pthread_mutex_lock(&lock);
        while (count == 0)
            pthread_cond_wait(&not_empty, &lock);

        int item = buffer[--count];
        printf("Consumed: %d\n", item);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_full);
    pthread_cond_destroy(&not_empty);
    return 0;
}
