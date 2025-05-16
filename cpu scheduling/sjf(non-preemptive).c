#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int completion;
    int waiting;
    int turnaround;
    int done;  // flag to check if process is completed
};

int main() {
    int n, i, completed = 0, time = 0;
    struct Process p[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].done = 0;
    }

    // SJF Non-Preemptive scheduling
    while(completed < n) {
        int idx = -1;
        int min_burst = 99999;

        // Find process with minimum burst time among arrived and not done
        for(i = 0; i < n; i++) {
            if(p[i].arrival <= time && p[i].done == 0 && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }

        if(idx != -1) {
            // Process found
            time += p[idx].burst;
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
            p[idx].done = 1;
            completed++;
        } else {
            // No process arrived yet, increment time
            time++;
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
   a. Among all processes that have arrived and are not completed,
      find the process with the smallest burst time.
   b. If such process is found:
      - Execute it completely (add its burst time to current time)
      - Calculate completion time, turnaround time, and waiting time
      - Mark the process as done and increase completed count
   c. If no process has arrived yet, increment time by 1 and check again
3. After all processes are done, calculate average waiting and turnaround times.
*/
