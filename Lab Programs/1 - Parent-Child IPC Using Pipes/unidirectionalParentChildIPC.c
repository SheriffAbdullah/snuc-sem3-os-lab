#include <stdio.h>
#include <unistd.h>

int main() {
    char text[20];
    
    int p;
    int fd[2];
    
    p = pipe(fd);
    
    // Pipe creation failed
    if (p < 0) {
        printf("Error in pipe creation.\n");
    }
    // Pipe creation successful
    else {
        int pid = fork();
    
        // Child process
        if (pid == 0) {
            close(fd[1]);
            read(fd[0], text, 20);
            printf("Message from Parent: %s\n", text);
        }
        // Parent process
        else {
            close(fd[0]);
            write(fd[1], "Hello, Child!", 20);
        }
    }
	
	return 0;
}

