#include <pthread.h>
#include <stdio.h>

static double num1 = 20.0;
static double num2 = 10.0;
static double add_result;
static double sub_result;
static double mul_result;
static double div_result;

static void *addition(void *arg) {
    (void)arg;
    add_result = num1 + num2;
    return NULL;
}

static void *subtraction(void *arg) {
    (void)arg;
    sub_result = num1 - num2;
    return NULL;
}

static void *multiplication(void *arg) {
    (void)arg;
    mul_result = num1 * num2;
    return NULL;
}

static void *division(void *arg) {
    (void)arg;
    if (num2 != 0.0) {
        div_result = num1 / num2;
    }
    return NULL;
}

int main(void) {
    pthread_t add_thread, sub_thread, mul_thread, div_thread;

    pthread_create(&add_thread, NULL, addition, NULL);
    pthread_create(&sub_thread, NULL, subtraction, NULL);
    pthread_create(&mul_thread, NULL, multiplication, NULL);
    pthread_create(&div_thread, NULL, division, NULL);

    pthread_join(add_thread, NULL);
    pthread_join(sub_thread, NULL);
    pthread_join(mul_thread, NULL);
    pthread_join(div_thread, NULL);

    printf("Addition: %.2f\n", add_result);
    printf("Subtraction: %.2f\n", sub_result);
    printf("Multiplication: %.2f\n", mul_result);
    printf("Division: %.2f\n", div_result);
    return 0;
}
