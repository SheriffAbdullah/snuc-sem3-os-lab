#include <stdio.h>
#include <unistd.h>

int main() {
	char text[20];
    
	int pipe1, pipe2;
	int fd1[2], fd2[2];
    
	pipe1 = pipe(fd1);
    if (pipe1 < 0) {
        printf("Error in pipe 1 creation.");
    }
    
	pipe2 = pipe(fd2);
    if (pipe1 < 0) {
        printf("Error in pipe 2 creation.");
    }
	
    // After forking, there will be 2 copies of every memory space allocated before 'fork()'.
	int pid = fork();
	
	// Child
	if (pid == 0) {
        // Close unwanted ends of pipe.
        // Close 'write' in 'pipe1'.
		close(fd1[1]);
        // Close 'read' in 'pipe2'.
		close(fd2[0]);
        
		read(fd1[0], text, 20);
		printf("Message from Parent: %s\n", text);

		write(fd2[1], "Hello, my Parent!", 20);
	}
	// Parent
	else {
        // Close unwanted ends of pipe.
		close(fd1[0]);
		close(fd2[1]);
        
		write(fd1[1], "Hello, my child!", 20);
        
		read(fd2[0], text, 20);
		printf("Message from Child: %s\n", text);
	}
	
	return 0;
}

/*
 Note:
 
 To visualize, assume there are 2 pipes.
 Parent process is on one side of the 2 pipes, and child process is on the other.
 
 Parent only writes to child in pipe 1 and does not listen in that pipe, while child only listens to parent (read) through pipe 1 and does not write through it.
 
 Parent only listens to child in pipe 2 and does not write in that pipe, while child only writes to parent through pipe 2 and does not listen through it.
 */
