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
    // when a child finishes, print its finish time in seconds and milliseconds
    // calculate the elapsed time 
    *seconds = end.tv_sec - start.tv_sec;
    *milliseconds = (end.tv_nsec - start.tv_nsec) / 1000000;
    if (*milliseconds < 0) {
        *seconds -= 1;
        *milliseconds += 1000;
    }
}

int main() {
    // starts the race by capturing the start time and preparing data structures
    pid_t pids[NUM_SLUGS]; // stores child PIDs 
    bool finished[NUM_SLUGS] = {false}; // tracks whether each child has finished
    struct timespec start_time, current_time;
    int remaining = NUM_SLUGS;
    // records high-resolution start time 
    clock_gettime(CLOCK_MONOTONIC, &start_time);
    printf("Starting the Slug Race!\n");

    // Spawn the children
    // create four child processes using a iterative loop, each running the slug with unique paramter
    for (int i = 0; i < NUM_SLUGS; i++) { // for loop with fork() 
        if ((pids[i] = fork()) == 0) { // Child process
            char arg[2];
            snprintf(arg, sizeof(arg), "%d", i + 1);
            execlp("./slug", "./slug", arg, NULL); // call execlp to replace the child process with the slug executable
            perror("execlp failed");
            exit(1);
        }
    }

    // Monitor the children
    while (remaining > 0) {
        // periodically check if any child process has finished. Use a loop and aviod blocking behavior
        usleep(SLEEP_INTERVAL);
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        for (int i = 0; i < NUM_SLUGS; i++) {
            if (!finished[i] && waitpid(pids[i], NULL, WNOHANG) > 0) {
                finished[i] = true;
                remaining--;
                // when a child finished, hte finish time in seconds and milliseconds is printed
                long seconds, milliseconds;
                getTimeDifference(start_time, current_time, &seconds, &milliseconds);
                printf("Slug %d finished in %ld.%03ld seconds\n", i + 1, seconds, milliseconds);
            }
        }

        printf("Race Status:\n"); // displays the current state of the race during each loop iteration 
        // iterate over all slugs and print their current state 
        for (int i = 0; i < NUM_SLUGS; i++) {
            printf(" Slug %d: %s\n", i + 1, finished[i] ? "Finished" : "Running");
        }
    }

    printf("The Slug Race is over!\n");
    // exits the loop when all children have finsihed and print a final message
    return 0;
}
