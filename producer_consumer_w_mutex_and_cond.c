#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5

// Shared buffer and associated variables
int buffer[BUFFER_SIZE];
int count = 0;  // Number of items in the buffer
pthread_mutex_t lock;  // Mutex for synchronizing access to the buffer
pthread_cond_t not_empty;  // Condition variable for notifying consumer
pthread_cond_t not_full;   // Condition variable for notifying producer

// Producer function
void* producer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);  // Acquire the mutex

        // Wait until the buffer is not full
        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&not_full, &lock); //RELEASES LOCK WHILE WAITING!!
        }

        // Produce an item
        buffer[count] = i;
        printf("Produced: %d\n", i);
        count++;

        pthread_cond_signal(&not_empty);  // Notify the consumer that the buffer is not empty
        pthread_mutex_unlock(&lock);  // Release the mutex

        // Simulate some production time
        sleep(rand() % 2);
    }
    return NULL;
}

// Consumer function
void* consumer(void* arg) {
    for (int i = 0; i < 10; i++) {
        pthread_mutex_lock(&lock);  // Acquire the mutex

        // Wait until the buffer is not empty
        while (count == 0) {
            pthread_cond_wait(&not_empty, &lock); //RELEASES LOCK WHILE WAITING!!
        }

        // Consume an item
        count--;
        int item = buffer[count];
        printf("Consumed: %d\n", item);

        pthread_cond_signal(&not_full);  // Notify the producer that the buffer is not full
        pthread_mutex_unlock(&lock);  // Release the mutex

        // Simulate some consumption time
        sleep(rand() % 2);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    pthread_mutex_init(&lock, NULL);  // Initialize the mutex
    pthread_cond_init(&not_empty, NULL);  // Initialize the condition variable
    pthread_cond_init(&not_full, NULL);   // Initialize the condition variable

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Wait for threads to finish
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    // Cleanup
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);

    return 0;
}
