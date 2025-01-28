#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <sys/wait.h>

#define NUM_SLUGS 4
#define SLEEP_INTERVAL 330000 // in microseconds

void getTimeDifference(struct timespec start, struct timespec end, long *seconds, long *milliseconds) {
    *seconds = end.tv_sec - start.tv_sec;
    *milliseconds = (end.tv_nsec - start.tv_nsec) / 1000000;
    if (*milliseconds < 0) {
        *seconds -= 1;
        *milliseconds += 1000;
    }
}

int main() {
    pid_t pids[NUM_SLUGS];
    bool finished[NUM_SLUGS] = {false};
    struct timespec start_time, current_time;
    int remaining = NUM_SLUGS;

    clock_gettime(CLOCK_MONOTONIC, &start_time);
    printf("[Parent]: Starting the Slug Race!\n");

    for (int i = 0; i < NUM_SLUGS; i++) {
        if ((pids[i] = fork()) == 0) { // Child process
            printf("[Child, PID: %d]: Executing './slug %d' command...\n", getpid(), i + 1);
            char arg[2];
            snprintf(arg, sizeof(arg), "%d", i + 1);
            char *args[] = {"./slug", arg, NULL};
            execvp("./slug", args); // replace child process
            perror("execvp failed");
            exit(1);
        } else if (pids[i] > 0) { // Parent process
            printf("[Parent]: I forked off child %d.\n", pids[i]);
        } else {
            perror("fork failed");
            exit(1);
        }
    }

    while (remaining > 0) {
        usleep(SLEEP_INTERVAL);
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        for (int i = 0; i < NUM_SLUGS; i++) {
            if (!finished[i] && waitpid(pids[i], NULL, WNOHANG) > 0) {
                finished[i] = true;
                remaining--;
                long seconds, milliseconds;
                getTimeDifference(start_time, current_time, &seconds, &milliseconds);
                printf("Child %d has crossed the finish line! It took %ld.%03ld seconds\n", pids[i], seconds, milliseconds);
            }
        }

        if (remaining > 0) {
            printf("The race is ongoing. The following children are still racing: ");
            for (int i = 0; i < NUM_SLUGS; i++) {
                if (!finished[i]) {
                    printf("%d ", pids[i]);
                }
            }
            printf("\n");
        }
    }

    printf("The race is over! It took %ld.%03ld seconds\n", 
           current_time.tv_sec - start_time.tv_sec, 
           (current_time.tv_nsec - start_time.tv_nsec) / 1000000);
    return 0;
}
