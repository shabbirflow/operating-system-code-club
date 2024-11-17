#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

// Shared variables
bool flag[2] = {false, false}; // Initially, neither process wants to enter the critical section
int turn = 0;                  // Initially, let P0 have the turn

void* process_0(void* arg) {
    // Entry section for process P0
    flag[0] = true;       // Indicate that P0 wants to enter the critical section
    turn = 1;             // Let P1 have the turn
    while (flag[1] && turn == 1) {
        // Busy wait until it's P0's turn or P1 is not interested
    }

    // Critical section
    printf("Process P0 is in the critical section\n");

    // Exit section for process P0
    flag[0] = false;      // Indicate that P0 has left the critical section

    return NULL;
}

void* process_1(void* arg) {
    // Entry section for process P1
    flag[1] = true;       // Indicate that P1 wants to enter the critical section
    turn = 0;             // Let P0 have the turn
    while (flag[0] && turn == 0) {
        // Busy wait until it's P1's turn or P0 is not interested
    }

    // Critical section
    printf("Process P1 is in the critical section\n");

    // Exit section for process P1
    flag[1] = false;      // Indicate that P1 has left the critical section

    return NULL;
}

int main() {
    pthread_t t0, t1;

    // Create two threads representing process P0 and process P1
    pthread_create(&t0, NULL, process_0, NULL);
    pthread_create(&t1, NULL, process_1, NULL);

    // Wait for the threads to finish
    pthread_join(t0, NULL);
    pthread_join(t1, NULL);

    return 0;
}
