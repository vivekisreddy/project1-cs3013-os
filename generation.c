#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void descendantFunction(int count) {
    if (count <= 0) {
        exit(0);
    }

    //child pid
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("[Child, PID: %d]: I was called with descendant count = %d and I'll have %d descendants.\n", getpid(), count, count - 1);
        descendantFunction(count - 1); //rercursive call
    } else {

        // to fork off a child process and wait for it using system calls, 
        // you would use the fork() function to create the child process and then use waitpid() 
        // to wait for the child to finish, and uses macros like WIFEXITED and WEXITSTATUS 
        // to properly interept the child's exit status within the parent process 
        // Parent process

        printf("[Parent, PID: %d]: I am waiting for PID %d to finish\n", getpid(), pid);
        int status;
        waitpid(pid, &status, 0); 
        if (WIFEXITED(status)) {
            int childExitCode = WEXITSTATUS(status);
            printf("[Parent, PID: %d]: Child %d finished with status code = %d. It’s now my turn to exit\n", getpid(), pid, childExitCode);
            exit(childExitCode + 1); 
        }
    }
}

int main() {
    //file open and reading
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

    srand(seed);

    //5 and 12 inclusive
    int minChild = 5;
    int maxChild = 12;
    int lifespanCount = minChild + (rand() % (maxChild - minChild + 1));
    printf("Random lifespan count: %d\n", lifespanCount);
    printf("Time to meet the kids/grandkids/great grand kids/...\n");

    //calling the recursive function
    descendantFunction(lifespanCount);

    return 0;
}
