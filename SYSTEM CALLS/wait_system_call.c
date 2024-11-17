#include <stdio.h>
#include <sys/wait.h> // for wait()
#include <unistd.h>   // for fork()

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process started, PID: %d\n", getpid());
        sleep(2); // Simulate some work with sleep
        printf("Child process finished.\n");
    } else {
        // Parent process
        printf("Parent waiting for child to finish.\n");
        wait(NULL);  // Wait for the child to finish
        printf("Parent process resumes after child has finished.\n");
    }

    return 0;
}
