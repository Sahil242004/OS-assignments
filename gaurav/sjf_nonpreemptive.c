#include <stdio.h>
#include <stdbool.h>

struct Process {
    int id, arrival, burst, start, finish;
    int waiting, turnaround;
    bool completed;
};

int main() {
    int n, completed = 0, time = 0;
    float total_waiting = 0, total_turnaround = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].completed = false;
    }

    printf("\nGantt Chart:\n");
    while (completed != n) {
        int idx = -1;
        int min_burst = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !p[i].completed && p[i].burst < min_burst) {
                min_burst = p[i].burst;
                idx = i;
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        p[idx].start = time;
        p[idx].finish = p[idx].start + p[idx].burst;
        p[idx].waiting = p[idx].start - p[idx].arrival;
        p[idx].turnaround = p[idx].finish - p[idx].arrival;
        p[idx].completed = true;
        completed++;
        time = p[idx].finish;

        total_waiting += p[idx].waiting;
        total_turnaround += p[idx].turnaround;

        printf("| P%d ", p[idx].id);
    }
    printf("|\n");

    printf("\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f", total_waiting / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_turnaround / n);
    return 0;
}

// Test Cases
// Enter number of processes: 4
// Enter arrival time and burst time for Process 1: 0 8
// Enter arrival time and burst time for Process 2: 1 4
// Enter arrival time and burst time for Process 3: 2 2
// Enter arrival time and burst time for Process 4: 3 1
