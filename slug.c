#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h> 

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <number between 1 and 4>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]); // Convert input to integer

    if (number < 1 || number > 4) {
        fprintf(stderr, "Invalid input. Please enter a number between 1 and 4.\n");
        return 1;
    }

    char filename[20];
    snprintf(filename, sizeof(filename), "seed_slug_%d.txt", number);

    FILE *seedFile = fopen(filename, "r");
    if (seedFile == NULL) {
        perror("Error opening seed file");
        return 1;
    }

    int seed;
    if (fscanf(seedFile, "%d", &seed) != 1) {
        perror("Error reading seed value");
        fclose(seedFile);
        return 1;
    }
    fclose(seedFile);

    printf("[SLUG PID: %d]: Read seed value: %d\n", getpid(), seed);
    printf("[SLUG PID: %d]: Read seed value (converted to integer): %d\n", getpid(), seed);

    srand(seed);

    int minTime = 2;
    int maxTime = 6;
    int numTime = minTime + (rand() % (maxTime - minTime + 1));
    int coinFlip = rand() % 2;
    printf("[Slug PID: %d] Delay time is %d seconds. Coin flip: %d\n", getpid(), numTime, coinFlip);
    printf("[Slug PID: %d] I’ll get the job done. Eventually...\n", getpid());
    sleep(numTime);

    if (coinFlip == 0) {
        printf("[SLUG PID: %d]: Break time is over! I am running the 'id -u -x' command.\n", getpid());
        execlp("last", "last", "-i", "-x", NULL);

    } else {
        printf("[SLUG PID: %d]: Break time is over! I am running the 'id --group' command.\n", getpid());
        execlp("id", "id", "--group", NULL);
    }

    perror("execlp failed");
    return 1;
}
