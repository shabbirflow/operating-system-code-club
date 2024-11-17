#include <iostream>
#include <thread>
#include <atomic>
#include <vector>

using namespace std;

const int N = 9; // Number of processes (P0 and P1)
atomic<int> number[N]; // Ticket numbers
atomic<bool> choosing[N]; // Indicates if a process is choosing a number

// Function to acquire the lock
void lock(int self) {
    choosing[self] = true; // Indicate that this process is choosing a number

    // Find the maximum number currently in use
    int max_number = 0;
    for (int i = 0; i < N; i++) {
        if (number[i] > max_number) {
            max_number = number[i];
        }
    }

    // Set the number for this process to one more than the maximum
    number[self] = max_number + 1;
    choosing[self] = false; // Indicate that choosing a number is done

    // Wait until other processes with smaller numbers or the same number but with a higher priority have finished
    for (int j = 0; j < N; j++) {
        if (j != self) {
            while (choosing[j]); // Wait if the other process is choosing a number
            while (number[j] != 0 && (number[j] < number[self] || (number[j] == number[self] && j < self)));
        }
    }
}

// Function to release the lock
void unlock(int self) {
    number[self] = 0; // Set the number to 0 to indicate this process is done
}

// Function to represent the critical section
void critical_section(int self) {
    cout << "Process " << self << " is in the critical section." << endl;
}

// Function executed by each thread
void thread_func(int self) {
    lock(self); // Acquire the lock
    critical_section(self); // Enter the critical section
    unlock(self); // Release the lock
}

int main() {
    // Initialize ticket numbers and choosing flags
    for (int i = 0; i < N; i++) {
        number[i] = 0;
        choosing[i] = false;
    }

    // Create threads for each process
    thread t1(thread_func, 0); // Process 0
    thread t2(thread_func, 1); // Process 1

    // Wait for both threads to complete
    t1.join();
    t2.join();

    return 0;
}
