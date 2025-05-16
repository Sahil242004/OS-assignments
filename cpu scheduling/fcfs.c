#include <stdio.h>

struct Process {
    int pid;           // Process ID
    int arrival;       // Arrival Time
    int burst;         // Burst Time
    int completion;    // Completion Time
    int turnaround;    // Turnaround Time
    int waiting;       // Waiting Time
};

int main() {
    int n, i, j;
    struct Process p[10];
    int time = 0;

    // Input number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    for(i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for process %d: ", p[i].pid);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
    }

    // ---------------------
    // PSEUDOCODE:
    // Sort processes by arrival time
    // time = 0
    //
    // for each process in sorted order:
    //     if time < arrival:
    //         time = arrival   // CPU waits if process not arrived
    //     completion = time + burst
    //     turnaround = completion - arrival
    //     waiting = turnaround - burst
    //     time = completion
    // ---------------------

    // Sort processes by arrival time (simple bubble sort)
    for(i = 0; i < n-1; i++) {
        for(j = 0; j < n-1-i; j++) {
            if(p[j].arrival > p[j+1].arrival) {
                struct Process temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }

    time = 0; // Current time starts at 0

    // Calculate completion, turnaround and waiting times
    for(i = 0; i < n; i++) {
        if(time < p[i].arrival) {
            time = p[i].arrival;  // CPU idle till process arrives
        }
        p[i].completion = time + p[i].burst;
        p[i].turnaround = p[i].completion - p[i].arrival;
        p[i].waiting = p[i].turnaround - p[i].burst;
        time = p[i].completion;  // update current time
    }

    // Display process info and average times
    int total_turnaround = 0, total_waiting = 0;
    printf("\nPID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");
    for(i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].arrival, p[i].burst,
               p[i].completion, p[i].turnaround, p[i].waiting);
        total_turnaround += p[i].turnaround;
        total_waiting += p[i].waiting;
    }

    printf("\nAverage Turnaround Time: %.2f\n", (float)total_turnaround / n);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting / n);

    return 0;
}
