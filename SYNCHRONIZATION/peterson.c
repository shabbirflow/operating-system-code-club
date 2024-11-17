#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define NUM_ITERATIONS 5

// Shared variables
volatile bool flag[2] = {false, false};  // Indicates interest in entering critical section
volatile int turn;                        // Indicates whose turn it is
int shared_variable = 0;                  // Shared resource

// Condition variables for blocking
pthread_cond_t cond[2];
pthread_mutex_t mutex;

void enter_critical_section(int process_id) {
    int other = 1 - process_id; // The ID of the other process

    // Indicate interest in entering the critical section
    flag[process_id] = true;
    turn = process_id; // Set turn to this process's ID

    // Wait until the other process is not interested or it's our turn
    pthread_mutex_lock(&mutex);
    while (flag[other] && turn == other) {
        pthread_cond_wait(&cond[process_id], &mutex);
    }
    pthread_mutex_unlock(&mutex);
}

void leave_critical_section(int process_id) {
    // Indicate that this process is leaving the critical section
    flag[process_id] = false;

    // Signal the other process to wake it up
    pthread_cond_signal(&cond[1 - process_id]);
}

void* process(void* id) {
    int process_id = *(int*)id;

    for (int i = 0; i < NUM_ITERATIONS; i++) {
        enter_critical_section(process_id);
        
        // Critical Section
        shared_variable++;
        printf("Process %d in critical section, shared variable: %d\n", process_id, shared_variable);
        sleep(1); // Simulate some work in the critical section

        leave_critical_section(process_id);
    }

    return NULL;
}

int main() {
    pthread_t threads[2];
    int ids[2] = {0, 1};

    // Initialize condition variables and mutex
    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond[0], NULL);
    pthread_cond_init(&cond[1], NULL);

    // Create two threads
    for (int i = 0; i < 2; i++) {
        pthread_create(&threads[i], NULL, process, (void*)&ids[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < 2; i++) {
        pthread_join(threads[i], NULL);
    }

    // Clean up
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond[0]);
    pthread_cond_destroy(&cond[1]);

    return 0;
}
