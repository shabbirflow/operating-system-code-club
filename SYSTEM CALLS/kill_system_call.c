#include <stdio.h>
#include <unistd.h>   // for fork(), kill()
#include <signal.h>   // for signal definitions

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Child process
        printf("Child process running, PID: %d\n", getpid());
        while (1);  // Infinite loop to keep child running
    } else {
        // Parent process
        printf("Parent process, PID: %d\n", getpid());
        sleep(1);  // Allow child to run for a second
        printf("Killing child process.\n");
        kill(pid, SIGKILL);  // Terminate the child process
    }

    return 0;
}
