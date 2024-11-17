#include <stdio.h>
#include <stdbool.h>
#include <unistd.h> // For sleep function

bool flag[2] = {false, false}; // Flags for each process
int turn; // Variable to indicate whose turn it is

void process0() {
    for (int i = 0; i < 5; i++) {
        // Indicate interest in entering the critical section
        flag[0] = true;
        turn = 1; // Give turn to Process 1

        // Wait until Process 1 is not interested or it is our turn
        while (flag[1] && turn == 1);

        // Critical Section
        printf("Process 0 is in the critical section\n");
        sleep(1); // Simulate work in the critical section

        // Exit Critical Section
        flag[0] = false; // Indicate no longer interested
        printf("Process 0 is leaving the critical section\n");
    }
}

void process1() {
    for (int i = 0; i < 5; i++) {
        // Indicate interest in entering the critical section
        flag[1] = true;
        turn = 0; // Give turn to Process 0

        // Wait until Process 0 is not interested or it is our turn
        while (flag[0] && turn == 0);

        // Critical Section
        printf("Process 1 is in the critical section\n");
        sleep(1); // Simulate work in the critical section

        // Exit Critical Section
        flag[1] = false; // Indicate no longer interested
        printf("Process 1 is leaving the critical section\n");
    }
}

int main() {
    if (fork() == 0) {
        // Child process - Process 1
        process1();
    } else {
        // Parent process - Process 0
        process0();
    }
    return 0;
}
