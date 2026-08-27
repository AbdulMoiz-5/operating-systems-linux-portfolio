#include <pthread.h>
#include <stdio.h>

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

static void *logger(void *arg) {
    int id = *(int *)arg;

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_lock(&lock);
        FILE *file = fopen("log.txt", "a");
        if (file != NULL) {
            fprintf(file, "Thread %d log %d\n", id, i);
            fclose(file);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(void) {
    pthread_t threads[3];
    int ids[3] = {1, 2, 3};

    for (int i = 0; i < 3; ++i)
        pthread_create(&threads[i], NULL, logger, &ids[i]);

    for (int i = 0; i < 3; ++i)
        pthread_join(threads[i], NULL);

    pthread_mutex_destroy(&lock);
    return 0;
}
