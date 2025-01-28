#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    // Step 1: Read the random seed value from seed.txt
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

    // Step 2: Seed the random number generator
    srand(seed);

    // Step 3: Define the directories
    const char *directories[] = {"/home", "/proc", "/proc/sys", "/usr", "/usr/bin", "/bin"};
    int numDirectories = 6;

    // Step 4: Explore the five directories
    for (int i = 0; i < 5; i++) {
        // Generate a random directory index
        int dirIndex = rand() % numDirectories;
        
        // Change the current working directory
        if (chdir(directories[dirIndex]) != 0) {
            perror("Changing directory failed");
            continue;
        }

        // Get and print the current working directory
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd failed");
            continue;
        }
        printf("Selection #%d: %s [SUCCESS]\n", i + 1, directories[dirIndex]);
        printf("Current reported directory: %s\n", cwd);

        // Fork a child process
        pid_t pid = fork();
        if (pid < 0) {
            perror("Fork failed");
            return 1;
        } else if (pid == 0) {
            // Child process
            printf("[Child, PID: %d]: Executing 'ls -tr' command...\n", getpid());
            char *args[] = {"ls", "-tr", NULL};
            execvp("ls", args);
            
            // If execvp fails
            perror("execvp failed");
            exit(1);
        } else {
            // Parent process
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                printf("[Parent]: Child %d finished with status code %d. Onward!\n", pid, WEXITSTATUS(status));
            }
        }
    }

    return 0;
}
