#include <stdio.h>
#include <pthread.h>

int counter = 0;  // Shared resource
pthread_mutex_t mutex;  // Mutex for synchronizing access

void* incrementCounter(void* arg) {
    for (int i = 0; i < 100000; i++) {
        pthread_mutex_lock(&mutex);   // Lock the mutex
        counter++;                    // Critical section
        pthread_mutex_unlock(&mutex); // Unlock the mutex
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);

    // Create two threads that increment the counter
    pthread_create(&t1, NULL, incrementCounter, NULL);
    pthread_create(&t2, NULL, incrementCounter, NULL);

    // Wait for both threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);  // Should be 200000

    return 0;
}
