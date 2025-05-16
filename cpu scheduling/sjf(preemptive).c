#include <stdio.h>
#include <limits.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
};

int main() {
    int n, i, completed = 0, time = 0, min_idx;
    int min_remaining;
    struct Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    while(completed < n) {
        min_remaining = INT_MAX;
        min_idx = -1;

        // Find process with minimum remaining time among arrived processes
        for(i = 0; i < n; i++) {
            if(p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min_remaining) {
                min_remaining = p[i].remaining;
                min_idx = i;
            }
        }

        if(min_idx == -1) {
            // No process has arrived yet or all remaining times are zero
            time++;
            continue;
        }

        // Execute process for 1 unit time
        p[min_idx].remaining--;
        time++;

        // If process finished executing
        if(p[min_idx].remaining == 0) {
            completed++;
            p[min_idx].completion = time;
            p[min_idx].turnaround = p[min_idx].completion - p[min_idx].arrival;
            p[min_idx].waiting = p[min_idx].turnaround - p[min_idx].burst;
        }
    }

    int total_waiting = 0, total_turnaround = 0;

    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        total_waiting += p[i].waiting;
        total_turnaround += p[i].turnaround;
    }

    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround / n);

    return 0;
}

/*
PSEUDOCODE (Simple Language):

1. Initialize time = 0, completed = 0
2. Repeat until all processes are completed:
   a. Among all arrived processes, find the one with the smallest remaining time.
   b. If no process has arrived yet, increment time by 1.
   c. Else, execute that process for 1 unit of time.
   d. Decrease the process’s remaining time by 1.
   e. If remaining time becomes zero, mark process as completed,
      record completion, turnaround and waiting times.
3. After all processes are done, calculate average waiting and turnaround times.
*/
