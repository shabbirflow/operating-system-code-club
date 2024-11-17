#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>

#define N 5 // Number of philosophers

std::vector<sem_t> forks(N); // Semaphores for each fork

// Function for a philosopher to think
void think(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Simulate thinking
    std::cout << "Philosopher " << id + 1 << " is thinking." << std::endl;
    std::cout << std::endl;

}

// Function for a philosopher to eat
void eat(int id) {
    std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Simulate eating
    std::cout << "Philosopher " << id + 1 << " is eating." << std::endl;
}

// Function representing the behavior of each philosopher
void philosopher(int id) {
    while (true) {
        think(id);

        int left = id;
        int right = (id + 1) % N;

        // Pick up forks (semaphores)
        sem_wait(&forks[left]);  // Pick up left fork
        sem_wait(&forks[right]); // Pick up right fork

        eat(id); // Eat

        // Put down forks (release semaphores)
        sem_post(&forks[right]); // Put down right fork
        sem_post(&forks[left]);  // Put down left fork
    }
}

int main() {
    std::vector<std::thread> philosophers(N);

    // Initialize semaphores
    for (int i = 0; i < N; ++i) {
        sem_init(&forks[i], 0, 1); // Initialize each fork semaphore to 1 (available)
    }

    // Create philosopher threads
    for (int i = 0; i < N; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }

    // Join philosopher threads
    for (auto& th : philosophers) {
        th.join();
    }

    // Destroy semaphores (not reached due to infinite loop in this example)
    for (int i = 0; i < N; ++i) {
        sem_destroy(&forks[i]);
    }

    return 0;
}
