#include <math.h>
#include <pthread.h>
#include <stdio.h>

typedef struct {
    double number;
    double result;
} Data;

static void *square(void *arg) {
    Data *data = arg;
    data->result = data->number * data->number;
    return NULL;
}

static void *square_root(void *arg) {
    Data *data = arg;
    data->result = sqrt(data->number);
    return NULL;
}

int main(void) {
    pthread_t square_thread, root_thread;
    Data square_data = {16.0, 0.0};
    Data root_data = {16.0, 0.0};

    pthread_create(&square_thread, NULL, square, &square_data);
    pthread_create(&root_thread, NULL, square_root, &root_data);
    pthread_join(square_thread, NULL);
    pthread_join(root_thread, NULL);

    printf("Square: %.2f\n", square_data.result);
    printf("Square root: %.2f\n", root_data.result);
    return 0;
}
