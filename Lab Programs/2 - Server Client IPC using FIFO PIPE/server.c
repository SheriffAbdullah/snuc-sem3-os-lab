#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{	
	// FIFO with All permissions enabled (Code = 0777) (0666 = No Executable permission = Also OK)
	mkfifo("database", 0777);
	
	int fd = open("database", O_RDONLY);

	char txt[100];
	int clientCount = 0;
    int line = 1;
	
    printf("*** Server Session Started ***\n\n");
    
	do {
		// Read
		read(fd, txt, 100);
        
		// Client has entered
		if (strcmp(txt, "enter") == 0)
		{
			clientCount++;
            continue;
		}
		
		// Client has left
		if (strcmp(txt, "exit") == 0)
		{
            clientCount--;
            continue;
		}
        
        printf("[%d] %s\n", line, txt);
        line++;
        
        /*
         (or)
         
         // Write to Server Screen -> 'write(<fd>, <string>, <len_of_string>)' where 'fd' = 1 will write in 'stdout'.
         write(1, txt, strlen(txt));
         write(1, "\n", 1);
         */
        
	} while(clientCount);
    
    printf("\n*** Server Session Ended ***\n");
    
	return 0;
}
