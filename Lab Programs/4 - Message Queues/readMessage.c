#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

struct Message {
	long key;
	char data[100];
} msg;

int main() {
	key_t key = ftok("database.txt", 60);
	int msgid = msgget(key, 0666|IPC_CREAT);
	printf("--- Message Queue #%d ---\n", msgid);
	
	int k = msgrcv(msgid, &msg, sizeof(msg), 1, 0);
	printf("Data received is: %s(Key: %ld)\n", msg.data, msg.key);
	
	msgctl(msgid, IPC_RMID, NULL);
	return 0;	
}
