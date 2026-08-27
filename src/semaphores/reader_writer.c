#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <time.h>

#define READERS 5
#define WRITERS 2
#define WRITES_PER_WRITER 5
#define TOTAL_WRITES (WRITERS * WRITES_PER_WRITER)

static int shared_value = 0;
static int active_readers = 0;
static int waiting_writers = 0;
static int writes_done = 0;
static sem_t writer_lock;
static sem_t reader_gate;
static pthread_mutex_t reader_count_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t writer_count_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t completion_lock = PTHREAD_MUTEX_INITIALIZER;

static void *writer(void *arg) {
    int id = *(int *)arg;
    for (int i = 0; i < WRITES_PER_WRITER; ++i) {
        pthread_mutex_lock(&writer_count_lock);
        ++waiting_writers;
        if (waiting_writers == 1) sem_wait(&reader_gate);
        pthread_mutex_unlock(&writer_count_lock);

        sem_wait(&writer_lock);
        shared_value += 10;
        printf("Writer %d -> %d\n", id, shared_value);

        pthread_mutex_lock(&completion_lock);
        ++writes_done;
        pthread_mutex_unlock(&completion_lock);

        sem_post(&writer_lock);

        pthread_mutex_lock(&writer_count_lock);
        --waiting_writers;
        if (waiting_writers == 0) sem_post(&reader_gate);
        pthread_mutex_unlock(&writer_count_lock);
        struct timespec ts = {0, 20000000};
        nanosleep(&ts, NULL);
    }
    return NULL;
}

static void *reader(void *arg) {
    int id = *(int *)arg;
    while (1) {
        pthread_mutex_lock(&completion_lock);
        int done = writes_done >= TOTAL_WRITES;
        pthread_mutex_unlock(&completion_lock);
        if (done) break;

        sem_wait(&reader_gate);
        pthread_mutex_lock(&reader_count_lock);
        ++active_readers;
        if (active_readers == 1) sem_wait(&writer_lock);
        pthread_mutex_unlock(&reader_count_lock);
        sem_post(&reader_gate);

        printf("Reader %d <- %d (active readers: %d)\n", id, shared_value, active_readers);

        pthread_mutex_lock(&reader_count_lock);
        --active_readers;
        if (active_readers == 0) sem_post(&writer_lock);
        pthread_mutex_unlock(&reader_count_lock);
        struct timespec ts = {0, 10000000};
        nanosleep(&ts, NULL);
    }
    return NULL;
}

int main(void) {
    pthread_t readers[READERS], writers[WRITERS];
    int reader_ids[READERS], writer_ids[WRITERS];

    sem_init(&writer_lock, 0, 1);
    sem_init(&reader_gate, 0, 1);

    for (int i = 0; i < READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }
    for (int i = 0; i < WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (int i = 0; i < WRITERS; ++i) pthread_join(writers[i], NULL);

    /* Wake readers that may still be waiting on the gate/data path. */
    for (int i = 0; i < READERS; ++i) pthread_join(readers[i], NULL);

    sem_destroy(&writer_lock);
    sem_destroy(&reader_gate);
    pthread_mutex_destroy(&reader_count_lock);
    pthread_mutex_destroy(&writer_count_lock);
    pthread_mutex_destroy(&completion_lock);
    return 0;
}
