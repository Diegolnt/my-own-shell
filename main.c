#include <stdio.h>
#include <unistd.h>
#include <string.h> // Needed for strlen
#include <sys/wait.h> // For wait()

int main(){
    
    int fd[2]; 
    // 1. IMPORTANT: Create the pipe BEFORE the fork so File Descriptors are inherited.
    if (pipe(fd) == -1) {
        perror("Pipe failed");
        return 1;
    }

    // 2. Now we fork. The Child inherits fd[0] and fd[1].
    int pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    // --- CHILD PROCESS ---
    if (pid == 0){
        // Child writes, so we close the Read End.
        close(fd[0]); 
        
        char *message = "Child Write Test";
        
        printf("Child (PID: %d): Writing to pipe...\n", getpid());
        
        // 3. Pass the 'message' pointer and its actual length.
        // We add +1 to strlen to include the 'null terminator' (\0), 
        // ensuring the reader gets a valid C-string.
        write(fd[1], message, strlen(message) + 1);
        
        close(fd[1]); // Close Write End to send EOF to the reader.
    }
    
    // --- PARENT PROCESS ---
    else {
        // Parent reads, so we close the Write End.
        close(fd[1]);
        
        char output[100];
        
        // Clear the buffer for safety
        memset(output, 0, sizeof(output));

        // read() blocks execution until data is available or the pipe is closed (EOF).
        read(fd[0], output, sizeof(output));
        
        printf("Parent (PID: %d): Received from child -> '%s'\n", getpid(), output);
        
        close(fd[0]);
        wait(NULL); // Best practice: wait for child to terminate to avoid a Zombie Process.
    }
    return 0;
}
