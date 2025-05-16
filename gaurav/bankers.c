
#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

int available[R]; // Available resources
int maximum[P][R]; // Maximum demand
int allocation[P][R]; // Currently allocated
int need[P][R]; // Remaining need

// Function to calculate need matrix
void calculateNeed() {
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            need[i][j] = maximum[i][j] - allocation[i][j];
}

// Safety Algorithm
bool isSafe() {
    int work[R];
    bool finish[P] = {false};
    int safeSeq[P];
    int count = 0;

    for (int i = 0; i < R; i++)
        work[i] = available[i];

    while (count < P) {
        bool found = false;
        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int j = 0; j < R; j++)
                        work[j] += allocation[i][j];

                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence: ");
    for (int i = 0; i < P; i++)
        printf("%d ", safeSeq[i]);
    printf("\n");

    return true;
}

// Resource Request Algorithm
bool requestResources(int process, int request[]) {
    for (int i = 0; i < R; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Request exceeds the process's maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Resources are not available. Process must wait.\n");
            return false;
        }
    }

    // Pretend to allocate resources
    for (int i = 0; i < R; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    // Check if safe
    if (isSafe())
        return true;

    // Rollback
    for (int i = 0; i < R; i++) {
        available[i] += request[i];
        allocation[process][i] -= request[i];
        need[process][i] += request[i];
    }

    printf("Request leads to unsafe state. Rolled back.\n");
    return false;
}

int main() {
    int i, j;

    printf("Enter available resources (R=%d):\n", R);
    for (i = 0; i < R; i++)
        scanf("%d", &available[i]);

    printf("Enter maximum matrix (%dx%d):\n", P, R);
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &maximum[i][j]);

    printf("Enter allocation matrix (%dx%d):\n", P, R);
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &allocation[i][j]);

    calculateNeed();

    isSafe();

    int process, request[R];
    char choice;
    do {
        printf("\nEnter process number making request (0 to %d): ", P - 1);
        scanf("%d", &process);

        printf("Enter resource request for process %d: ", process);
        for (i = 0; i < R; i++)
            scanf("%d", &request[i]);

        requestResources(process, request);

        printf("Do you want to make another request? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

//Enter available resources (R=3):
//3 3 2

//Enter maximum matrix (5x3):
//7 5 3
//3 2 2
//9 0 2
//2 2 2
//4 3 3

//Enter allocation matrix (5x3):
//0 1 0
//2 0 0
//3 0 2
//2 1 1
//0 0 2

//Request leads to safe state

//Enter process number making request (0 to 4): 1
//Enter resource request for process 1: 1 0 2

//Request leads to unsafe state

//Enter process number making request (0 to 4): 0
//Enter resource request for process 0: 3 3 0