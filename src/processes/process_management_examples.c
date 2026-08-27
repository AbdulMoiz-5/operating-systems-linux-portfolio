#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        printf("Child PID: %ld\n", (long)getpid());
        printf("Parent PID: %ld\n", (long)getppid());
        return 0;
    }

    printf("Parent PID: %ld\n", (long)getpid());
    printf("Created child PID: %ld\n", (long)pid);

    if (waitpid(pid, NULL, 0) == -1) {
        perror("waitpid");
        return EXIT_FAILURE;
    }

    puts("Child completed; parent continues.");
    return 0;
}
