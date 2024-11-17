#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define MAX_CUSTOMERS 5
#define NUM_CHAIRS 3

// Semaphores for synchronization
sem_t barber_sem;     // Barber semaphore
sem_t customer_sem;   // Customer semaphore
sem_t mutex;          // Mutex for critical section

int waiting_customers = 0; // Number of waiting customers

void* barber(void* arg) {
    while (1) {
        printf("The barber is sleeping...\n");
        sem_wait(&barber_sem); // Wait for a customer

        sem_wait(&mutex); // Enter critical section
        if (waiting_customers > 0) {
            waiting_customers--; // Serve a customer
            printf("The barber is cutting hair for a customer.\n");
            sem_post(&customer_sem); // Signal that haircut is done
        }
        sem_post(&mutex); // Exit critical section

        // Simulate haircut duration
        sleep(rand() % 5 + 1);
        printf("The barber has finished cutting hair.\n");
    }
}

void* customer(void* arg) {
    int customer_id = *(int*)arg;
    sleep(rand() % 5); // Simulate arrival time

    sem_wait(&mutex); // Enter critical section
    if (waiting_customers < NUM_CHAIRS) {
        waiting_customers++; // Add customer to waiting room
        printf("Customer %d is waiting in the waiting room.\n", customer_id);
        sem_post(&barber_sem); // Wake up the barber
        sem_post(&mutex); // Exit critical section

        sem_wait(&customer_sem); // Wait for haircut to finish
        printf("Customer %d has finished getting a haircut.\n", customer_id);
    } else {
        printf("Customer %d is leaving because the waiting room is full.\n", customer_id);
    }
    return NULL;
}

int main() {
    srand(time(NULL)); // Seed for random number generation

    pthread_t barber_thread;
    pthread_t customer_threads[MAX_CUSTOMERS];
    int customer_ids[MAX_CUSTOMERS];

    // Initialize semaphores
    sem_init(&barber_sem, 0, 0);
    sem_init(&customer_sem, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create barber thread
    pthread_create(&barber_thread, NULL, barber, NULL);

    // Create customer threads
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        customer_ids[i] = i + 1; // Customer IDs start from 1
        pthread_create(&customer_threads[i], NULL, customer, &customer_ids[i]);
    }

    // Wait for customer threads to finish
    for (int i = 0; i < MAX_CUSTOMERS; i++) {
        pthread_join(customer_threads[i], NULL);
    }

    // Cleanup
    sem_destroy(&barber_sem);
    sem_destroy(&customer_sem);
    sem_destroy(&mutex);

    return 0;
}
