#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define BUFFER_SIZE 10
#define PRODUCERS 3
#define CONSUMERS 3
#define ITEMS_PER_PRODUCER 20
#define TOTAL_ITEMS (PRODUCERS * ITEMS_PER_PRODUCER)

static int buffer[BUFFER_SIZE];
static int in = 0, out = 0, consumed = 0;
static sem_t empty_slots, full_slots;
static pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;

static void *producer(void *arg) {
    int id = *(int *)arg;
    for (int i = 1; i <= ITEMS_PER_PRODUCER; ++i) {
        sem_wait(&empty_slots);
        pthread_mutex_lock(&buffer_lock);
        buffer[in] = id * 100 + i;
        printf("Producer %d -> %d\n", id, buffer[in]);
        in = (in + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&buffer_lock);
        sem_post(&full_slots);
    }
    return NULL;
}

static void *consumer(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&count_lock);
        if (consumed >= TOTAL_ITEMS) {
            pthread_mutex_unlock(&count_lock);
            break;
        }
        ++consumed;
        pthread_mutex_unlock(&count_lock);

        sem_wait(&full_slots);
        pthread_mutex_lock(&buffer_lock);
        int item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        pthread_mutex_unlock(&buffer_lock);
        sem_post(&empty_slots);
        printf("Consumer %d <- %d\n", id, item);
    }
    return NULL;
}

int main(void) {
    pthread_t producers[PRODUCERS], consumers[CONSUMERS];
    int producer_ids[PRODUCERS], consumer_ids[CONSUMERS];

    sem_init(&empty_slots, 0, BUFFER_SIZE);
    sem_init(&full_slots, 0, 0);

    for (int i = 0; i < PRODUCERS; ++i) {
        producer_ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &producer_ids[i]);
    }
    for (int i = 0; i < CONSUMERS; ++i) {
        consumer_ids[i] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &consumer_ids[i]);
    }

    for (int i = 0; i < PRODUCERS; ++i) pthread_join(producers[i], NULL);
    for (int i = 0; i < CONSUMERS; ++i) sem_post(&full_slots);
    for (int i = 0; i < CONSUMERS; ++i) pthread_join(consumers[i], NULL);

    sem_destroy(&empty_slots);
    sem_destroy(&full_slots);
    pthread_mutex_destroy(&buffer_lock);
    pthread_mutex_destroy(&count_lock);
    return 0;
}
