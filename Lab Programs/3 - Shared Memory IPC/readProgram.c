#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	key_t key = ftok("myfile", 60);
	int shmid = shmget(key, 1024, 0666|IPC_CREAT);
	char *str = (char *) shmat(shmid, 0, 0);
	fgets(str, 100, stdin);
	
	return 0;
}
