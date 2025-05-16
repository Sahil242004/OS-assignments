#include <stdio.h>

struct Process {
    int pid;
    int arrival;
    int burst;
    int remaining;
    int waiting;
    int turnaround;
};

int main() {
    int n, time_quantum;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter arrival time and burst time for Process %d: ", i + 1);
        scanf("%d %d", &p[i].arrival, &p[i].burst);
        p[i].remaining = p[i].burst;
        p[i].waiting = 0;
        p[i].turnaround = 0;
    }

    printf("Enter time quantum: ");
    scanf("%d", &time_quantum);

    int complete = 0, time = 0;
    int queue[100], front = 0, rear = 0;
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    printf("\nGantt Chart:\n|");

    while (complete < n) {
        // Add newly arrived processes to queue
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if (front == rear) {
            time++;
            continue;
        }

        int idx = queue[front++];
        printf(" P%d |", p[idx].pid);

        int exec_time = (p[idx].remaining > time_quantum) ? time_quantum : p[idx].remaining;
        time += exec_time;
        p[idx].remaining -= exec_time;

        // Add new arrivals during execution
        for (int i = 0; i < n; i++) {
            if (p[i].arrival <= time && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        // Re-add if not finished
        if (p[idx].remaining > 0) {
            queue[rear++] = idx;
        } else {
            complete++;
            p[idx].turnaround = time - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;
        }
    }

    float total_wt = 0, total_tat = 0;
    printf("\n\nProcess\tArrival\tBurst\tWaiting\tTurnaround\n");
    for (int i = 0; i < n; i++) {
        total_wt += p[i].waiting;
        total_tat += p[i].turnaround;
        printf("P%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].arrival, p[i].burst, p[i].waiting, p[i].turnaround);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}


// Test Cases
// Enter number of processes: 4
// Enter arrival time and burst time for Process 1: 0 5
// Enter arrival time and burst time for Process 2: 1 4
// Enter arrival time and burst time for Process 3: 2 2
// Enter arrival time and burst time for Process 4: 3 1
// Enter time quantum: 2

