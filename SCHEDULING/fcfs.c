#include <stdio.h>

struct Process {
    int pid;         // Process ID
    int arrivalTime; // Arrival Time
    int burstTime;   // Burst Time
    int startTime;   // Start Time
    int endTime;     // End Time
};

// FCFS Scheduling Algorithm
void fcfs(struct Process processes[], int n) {
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        // Start time for the process is either the current time or the process's arrival time (whichever is later)
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Calculate the start and end time of the process
        processes[i].startTime = currentTime;
        processes[i].endTime = processes[i].startTime + processes[i].burstTime;

        // Move the current time forward by the burst time
        currentTime = processes[i].endTime;

        printf("Process %d starts at %d and finishes at %d\n", 
               processes[i].pid, processes[i].startTime, processes[i].endTime);
    }
}

int main() {
    struct Process processes[] = {
        {1, 0, 5, 0, 0}, // Process P1: Arrival Time = 0, Burst Time = 5
        {2, 1, 3, 0, 0}, // Process P2: Arrival Time = 1, Burst Time = 3
        {3, 2, 8, 0, 0}  // Process P3: Arrival Time = 2, Burst Time = 8
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    // Run the FCFS scheduling algorithm
    fcfs(processes, n);

    return 0;
}
