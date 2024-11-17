#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

sem_t read_lock;   // Semaphore for readers
sem_t write_lock;  // Semaphore for writers
int read_count = 0; // Number of readers accessing the resource

void *reader(void *arg) {
    int id = *((int *)arg);
    
    // Start reading
    sem_wait(&read_lock); // Wait to access read_count
    read_count++;          // Increment reader count
    if (read_count == 1) {
        sem_wait(&write_lock); // First reader locks the writer
    }
    sem_post(&read_lock); // Release access to read_count

    // Critical section: reading
    printf("Reader %d is reading.\n", id);
    // Simulate reading time
    sleep(1);

    // End reading
    sem_wait(&read_lock); // Wait to access read_count
    read_count--;         // Decrement reader count
    if (read_count == 0) {
        sem_post(&write_lock); // Last reader unlocks the writer
    }
    sem_post(&read_lock); // Release access to read_count
    
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    
    // Start writing
    sem_wait(&write_lock); // Wait for exclusive access
    
    // Critical section: writing
    printf("Writer %d is writing.\n", id);
    // Simulate writing time
    sleep(2);

    // End writing
    sem_post(&write_lock); // Release exclusive access

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];
    int reader_ids[5], writer_ids[5];

    sem_init(&read_lock, 0, 1); // Initialize read_lock semaphore
    sem_init(&write_lock, 0, 1); // Initialize write_lock semaphore

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < 5; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < 5; i++) {
        pthread_join(writers[i], NULL);
    }

    // Cleanup
    sem_destroy(&read_lock);
    sem_destroy(&write_lock);

    return 0;
}
