#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>
#include <sys/types.h>

struct Message {
	long key;
	char data[100];
} msg;

int main() {
	key_t key = ftok("database.txt", 60);
	int msgid = msgget(key, 0666|IPC_CREAT);
	msg.key = 1;
	
	printf("Write data in Message Queue #%d: ", msgid);
	fgets(msg.data, 100, stdin);
	
	msgsnd(msgid, &msg, sizeof(msg), 0);
	printf("Data sent is: %s(Key: %ld)\n", msg.data, msg.key);
	
	return 0;
}


/*
Note: 'fcntl.h' - NOT 'fnctl.h'
*/
