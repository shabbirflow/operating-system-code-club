#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;  // Process ID (PID)
    
    // Create a new process using fork()
    pid = fork();

    if (pid < 0) {
        // Fork failed
        fprintf(stderr, "Fork Failed");
        return 1;
    } else if (pid == 0) {
        // Child process (fork returns 0 in child)
        printf("Child Process: My PID is %d\n", getpid());
        printf("Child Process: My Parent's PID is %d\n", getppid());
    } else {
        // Parent process (fork returns child's PID in parent)
        printf("Parent Process: My PID is %d\n", getpid());
        printf("Parent Process: My Child's PID is %d\n", pid);
    }

    return 0;
}
