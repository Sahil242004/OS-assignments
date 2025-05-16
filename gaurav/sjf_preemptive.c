#include <stdio.h>
#include <limits.h>

struct Process {
    int id, arrival, burst, remaining, start, finish;
    int waiting, turnaround;
};

int main() {
    int n, completed = 0, time = 0, min_index;
    float total_waiting = 0, total_turnaround = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", p[i].id);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].start = -1;
    }

    printf("\nGantt Chart:\n");
    while (completed != n) {
        int shortest = -1;
        int min_remaining = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && p[i].remaining > 0 && p[i].remaining < min_remaining) {
                min_remaining = p[i].remaining;
                shortest = i;
            }
        }

        if (shortest == -1) {
            time++;
            continue;
        }

        if (p[shortest].start == -1)
            p[shortest].start = time;

        printf("| P%d ", p[shortest].id);
        p[shortest].remaining--;
        time++;

        if (p[shortest].remaining == 0) {
            p[shortest].finish = time;
            p[shortest].turnaround = p[shortest].finish - p[shortest].arrival;
            p[shortest].waiting = p[shortest].turnaround - p[shortest].burst;
            total_waiting += p[shortest].waiting;
            total_turnaround += p[shortest].turnaround;
            completed++;
        }
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

