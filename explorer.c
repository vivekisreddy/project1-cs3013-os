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
    printf("Read seed value (converted to integer): %d\n", seed);

    // Step 2: Seed the random number generator
    srand(seed);

    // Step 3: Define the directories 
    // it is an array of string pointers, where each pointer points to a null-terminated string representing a direcotry path
    const char *directories[] = {"/home", "/proc", "/proc/sys", "/usr", "/usr/bin", "/bin"}; //define the directories and put them in an array
    int numDirectories = 6; 
   
   // Step 4: Explore the five directories 
   for (int i = 0; i < 5; i++) { 
    // generates a random directory index 
    int dirIndex = rand() % numDirectories; // uses the modulo operator to select one of the six predefined directories for each iteration 
    // changes the current working directory 
    if (chdir(directories[dirIndex]) != 0) { // changes the current working directory
        perror("changing direcotry failed"); 
        continue; 
    }
    // get and print the current working 
    char cwd[1024]; 
    if (getcwd(cwd, sizeof(cwd)) == NULL) { // retrives the absolute path of the current directory
        perror("getcwd failed"); 
        continue; 
    }
    printf("Selection #%d: %s [SUCCESS]\n", i+1, directories[dirIndex]); 
    printf("Current reported directory: %s\n", cwd); 

    // fork a child process 
    pid_t pid = fork(); 
    if (pid < 0) { 
        perror("Fork failed"); 
        return 1; 
    } else if (pid == 0) { // a child process is created using fork() and the child runs the ls -tr command using execlp() 
        // child process 
        printf("[Child, PID: %d]: Executing 'ls -tr' command...\n", getpid()); 
        execlp("ls", "ls", "-tr", NULL); 
        // if execlp fails 
        perror("execlp failed"); 
        exit(1); 
    } else { 
        // parent process 
        // the parent waits for the child to complete and retrives the child's exit status
        int status; 
        waitpid(pid, &status, 0); 
        if (WIFEXITED(status)) { 
            printf("[Panret]: Child %d finished with status code %d. Onward!\n", pid, WEXITSTATUS(status)); 
        }
    }

    }
    return 0; 

}