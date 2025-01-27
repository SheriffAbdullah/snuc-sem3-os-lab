#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main()
{
	int fd = open("database", O_WRONLY);
	char txt[100];
	    
	write(fd, "enter", 100);
    printf("Established connection with Server. \n\n");
    
	while(1)
	{
        printf(">>> ");
		
        // '%s' -> Will read until whitespace
        // '%[^\n]s' -> Will read until newline
        scanf("%[^\n]s", txt);
		scanf("%*c");
		
		// Write to database (here, db = FIFO Pipe)
		write(fd, txt, 100);
		
		if (strcmp(txt, "exit") == 0)
		{
			printf("\nConnection terminated. \n");
			break;
		}
	}
		
	return 0;
}
