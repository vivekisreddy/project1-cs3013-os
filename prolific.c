#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    FILE *seedFile = fopen("seed.txt", "r");
    if (seedFile == NULL) {
        perror("Failed to open seed.txt");
        return 1;
    }
    int seed;
    if (fscanf(seedFile, "%d", &seed) != 1) {
        perror("Error reading seed value");
        fclose(seedFile);
        return 1;
    }
    fclose(seedFile);
    printf("Read seed value: %d\n", seed);
    printf("Read seed value (converted to integer): %d\n", seed);

    srand(seed);

    int minChild = 8;
    int maxChild = 13;
    int numChild = minChild + (rand() % (maxChild - minChild + 1));
    printf("Random Child Count: %d\n", numChild);
    printf("I’m feeling prolific!\n");

    for (int i = 0; i < numChild; i++) {
        pid_t pid = fork(); 
        if (pid < 0) { 
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            int waitTime = (rand() % 3) + 1;   
            int exitCode = (rand() % 50) + 1; 
            printf("[Child, PID: %d]: I am the child and I will wait %d seconds and exit with code %d.\n", getpid(), waitTime, exitCode);
            sleep(waitTime);
            printf("[Child, PID: %d]: Now exiting...\n", getpid());
            exit(exitCode);
        } else { 
            // to fork off a child process and wait for it using system calls, 
            // you would use the fork() function to create the child process and then use waitpid() 
            // to wait for the child to finish, and uses macros like WIFEXITED and WEXITSTATUS 
            // to properly interept the child's exit status within the parent process 
            
            // Parent process
            printf("[Parent]: I am waiting for PID %d to finish.\n", pid);
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) { // The WIFEXITED checks if the child process exited normally (not by signal)
                printf("[Parent]: Child %d finished with status code %d. Onward!\n", pid, WEXITSTATUS(status)); // Retrieves the exit status of the child process if it exited normally
            }
        }
    }

    return 0;
}
