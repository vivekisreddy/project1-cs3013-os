#include <stdio.h>   
#include <stdlib.h>  
#include <unistd.h>   
#include <sys/wait.h> 
#include <time.h>     

int main() {
    FILE *seedFile = fopen("seed.txt", "r"); // Open the file containing the seed value
    if (seedFile == NULL) {                 // Check if the file exists
        perror("Failed to open seed.txt");
        return 1; // Exit with error
    }

    int seed;
    if (fscanf(seedFile, "%d", &seed) != 1) { // Read the seed value from the file
        perror("Error reading seed value");
        fclose(seedFile); // Close the file and exit if the read fails
        return 1;
    }
    fclose(seedFile); // Close the file after reading
    printf("Read seed value: %d\n", seed);

    srand(seed); // Initialize random number generator with the seed

    int minChild = 8, maxChild = 13;
    int numChild = minChild + (rand() % (maxChild - minChild + 1)); // Generate random number of child processes
    printf("Random Child Count: %d\n", numChild);
    printf("I’m feeling prolific!\n");

    for (int i = 0; i < numChild; i++) { // Loop to create child processes
        pid_t pid = fork(); // Create a new process
        if (pid < 0) {      // Handle fork failure
            perror("Fork failed");
            return 1;
        } else if (pid == 0) { // Child process logic
            srand(time(NULL) ^ getpid()); // Reseed random generator uniquely for each child
            int waitTime = (rand() % 3) + 1; // Random wait time between 1-3 seconds
            int exitCode = (rand() % 50) + 1; // Random exit code between 1-50
            printf("[Child, PID: %d]: Waiting %d seconds, exiting with code %d.\n", getpid(), waitTime, exitCode);
            sleep(waitTime); // Simulate work by sleeping
            printf("[Child, PID: %d]: Now exiting...\n", getpid());
            exit(exitCode); // Terminate child process with exit code
        } else { // Parent process logic
            printf("[Parent]: Waiting for PID %d to finish.\n", pid);
            int status;
            waitpid(pid, &status, 0); // Wait for the specific child process
            if (WIFEXITED(status)) { // Check if the child exited normally
                printf("[Parent]: Child %d finished with status code %d.\n", pid, WEXITSTATUS(status));
            }
        }
    }

    return 0; // Program completes successfully
}
