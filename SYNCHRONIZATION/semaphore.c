#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int value;               // Semaphore value
    pthread_mutex_t mutex;   // Mutex for synchronization
    pthread_cond_t cond;     // Condition variable for waiting
} Semaphore;

// Initialize the semaphore
void sem_init(Semaphore* sem, int value) {
    sem->value = value;
    pthread_mutex_init(&sem->mutex, NULL);
    pthread_cond_init(&sem->cond, NULL);
}

// Wait operation (P)
void sem_wait(Semaphore* sem) {
    pthread_mutex_lock(&sem->mutex);
    while (sem->value <= 0) { // Block if the value is zero
        pthread_cond_wait(&sem->cond, &sem->mutex);
    }
    sem->value--; // Decrement the semaphore value
    pthread_mutex_unlock(&sem->mutex);
}

// Signal operation (V)
void sem_signal(Semaphore* sem) {
    pthread_mutex_lock(&sem->mutex);
    sem->value++; // Increment the semaphore value
    pthread_cond_signal(&sem->cond); // Wake up one waiting thread
    pthread_mutex_unlock(&sem->mutex);
}

// Example usage
void* thread_function(void* arg) {
    Semaphore* sem = (Semaphore*)arg;
    sem_wait(sem);
    printf("Thread %ld is in the critical section.\n", pthread_self());
    sleep(1); // Simulate some work
    printf("Thread %ld is leaving the critical section.\n", pthread_self());
    sem_signal(sem);
    return NULL;
}

int main() {
    pthread_t threads[5];
    Semaphore sem;
    
    sem_init(&sem, 1); // Initialize the semaphore to 1 (binary semaphore)

    for (int i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, thread_function, (void*)&sem);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
