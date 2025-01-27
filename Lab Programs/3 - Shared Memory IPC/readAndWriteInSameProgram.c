#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	// Generate key - ftok(<file_name>, <memory/process_id?>)
	key_t key = ftok("", 60);
	// Generate SHared Memory IDentifier [SHMID] - shmget(<key>, <num_of_bytes>, <read/write/executable_permissions>)
	int shmid = shmget(key, 1024, 0666|IPC_CREAT);
	// Create a string in that shared memory - shmat(<shmid>, <memory_address_space>, <flags>)
	char *str = (char *) shmat(shmid, 0, 0);
	// fgets(<string_to_read_to>, <max_characters>, <file_to_read_from>)
	fgets(str, 100, stdin);
	printf("%s", str);
	
	return 0;
}
