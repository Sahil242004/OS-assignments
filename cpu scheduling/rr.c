#include <stdio.h>

struct Process {
    int pid;            // Process ID
    int burst;          // Burst Time
    int remaining;      // Remaining Burst Time
    int arrival;        // Arrival Time
    int completion;     // Completion Time
    int waiting;        // Waiting Time
    int turnaround;     // Turnaround Time
};

int main() {
    int n, i, time = 0, count = 0;
    int quantum;

    struct Process p[10];

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input arrival and burst times
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
    }

    // Input time quantum
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    // ------------------------
    // PSEUDOCODE:
    // Initialize time = 0, completed_processes = 0
    // While completed_processes < n:
    //   for each process:
    //     if process has arrived and remaining > 0:
    //       run process for min(quantum, remaining)
    //       update time
    //       decrement remaining time
    //       if remaining == 0:
    //         completion = current time
    //         calculate turnaround and waiting times
    //         increment completed_processes
    // ------------------------

    int completed = 0;
    int mark[10] = {0}; // marks processes already completed

    while (completed < n) {
        int done = 1;
        for (i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0) {
                done = 0; // at least one process can be run

                // Run for quantum or remaining time, whichever is smaller
                int run_time = (p[i].remaining > quantum) ? quantum : p[i].remaining;
                time += run_time;
                p[i].remaining -= run_time;

                // If process finished executing
                if (p[i].remaining == 0) {
                    p[i].completion = time;
                    p[i].turnaround = p[i].completion - p[i].arrival;
                    p[i].waiting = p[i].turnaround - p[i].burst;
                    completed++;
                }
            }
            else if (p[i].arrival > time) {
                // If no process has arrived, increment time
                // to earliest arrival to avoid infinite loop
                int min_arrival = 9999;
                for (int k = 0; k < n; k++) {
                    if (p[k].remaining > 0 && p[k].arrival < min_arrival && p[k].arrival > time) {
                        min_arrival = p[k].arrival;
                    }
                }
                if(min_arrival != 9999)
                    time = min_arrival;
                break;
            }
        }
        if(done == 1) { 
            // No processes ready to run yet, increment time
            time++;
        }
    }

    // Print results
    int total_turnaround = 0, total_waiting = 0;
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        total_turnaround += p[i].turnaround;
        total_waiting += p[i].waiting;
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting / n);

    return 0;
}
