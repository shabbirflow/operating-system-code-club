#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 100

// Define the process structure
struct process {
    int pid;               // Process ID
    int burst_time;        // Total burst time required for process
    int arrival_time;     // Arrival time of the process
    int waiting_time;     // Waiting time of the process
    int turnaround_time;  // Turnaround time of the process
};

// Function to sort processes based on arrival time
void sortByArrival(struct process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrival_time > processes[j].arrival_time) {
                struct process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }
}

// Function to find waiting and turnaround times
void calculateTimes(struct process processes[], int n) {
    int completion_time = 0;
    int remaining_burst[MAX_PROCESSES];
    
    // Initialize remaining burst times
    for (int i = 0; i < n; i++) {
        remaining_burst[i] = processes[i].burst_time;
    }

    bool completed[MAX_PROCESSES] = {false};
    int count = 0;

    while (count < n) {
        int min_burst = 1e9; // Initialize to a large number
        int shortest = -1;
        
        // Find the process with the shortest burst time that has arrived and not completed
        for (int i = 0; i < n; i++) {
            if (!completed[i] && processes[i].arrival_time <= completion_time &&
                processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            completion_time++;
            continue;
        }

        // Update process times
        processes[shortest].waiting_time = completion_time - processes[shortest].arrival_time;
        processes[shortest].turnaround_time = processes[shortest].waiting_time + processes[shortest].burst_time;
        completion_time += processes[shortest].burst_time;
        completed[shortest] = true;
        count++;
    }
}

int main() {
    int n = 4; // Number of processes
    struct process processes[MAX_PROCESSES] = {
        {1, 6, 0, 0, 0}, 
        {2, 8, 1, 0, 0}, 
        {3, 7, 2, 0, 0}, 
        {4, 3, 3, 0, 0}
    };

    // Sort processes based on arrival time
    sortByArrival(processes, n);

    // Calculate waiting and turnaround times
    calculateTimes(processes, n);

    // Print the results
    printf("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");

    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
    }

    float avg_waiting_time = (float) total_waiting_time / n;
    float avg_turnaround_time = (float) total_turnaround_time / n;

    printf("The Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("The Average Turnaround Time: %.2f\n", avg_turnaround_time);

    return 0;
}
