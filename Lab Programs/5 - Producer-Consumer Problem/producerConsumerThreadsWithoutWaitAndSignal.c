#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_SIZE 3

// Stack-based buffer implementation. Queue = Better.
int stack[MAX_SIZE];
int count = -1;

pthread_mutex_t myLock;
	
void producer(int prod) {
    while(true) {
    //printf("Sleep Producer #%d.\n", prod);
        sleep((rand() % 10));

        // Free to write
        if (count < MAX_SIZE - 1) {
	    	pthread_mutex_lock(&myLock);
	    	count++;
	    	stack[count] = prod;
	    	pthread_mutex_unlock(&myLock);
	    	
	    	printf("#%d produced.\n", prod); fflush(stdout);
        }
        // Buffer full - wait for consumer to read
    }
}

void consumer(int cons) {
    while (true) {
    //printf("Sleep Consumer #%d.\n", cons);
        sleep((rand() % 10));
        // No content to read
        if (count >= 0) {
	    	pthread_mutex_lock(&myLock);
	    	// Content to read = Available
		printf("Consumer #%d consumed #%d\n", cons, stack[count]); fflush(stdout);
	    	count--;
	    	pthread_mutex_unlock(&myLock);
            
        }
        // Buffer empty - Wait for producer to write
    }
}

int main() {
	// Producers
	pthread_t t0, t1, t2, t3, t4;
	// Consumers
	pthread_t t5, t6, t7, t8, t9;
	
	pthread_create(&t5, NULL, (void *)consumer, (void *)0);
	pthread_create(&t0, NULL, (void *)producer, (void *)0);
	pthread_create(&t6, NULL, (void *)consumer, (void *)1);
	pthread_create(&t1, NULL, (void *)producer, (void *)1);
	pthread_create(&t7, NULL, (void *)consumer, (void *)2);
	pthread_create(&t3, NULL, (void *)producer, (void *)3);
	pthread_create(&t8, NULL, (void *)consumer, (void *)3);
	pthread_create(&t2, NULL, (void *)producer, (void *)2);
	pthread_create(&t9, NULL, (void *)consumer, (void *)4);
	pthread_create(&t4, NULL, (void *)producer, (void *)4);
	
   	pthread_join(t0, NULL);
   	pthread_join(t1, NULL);
    	pthread_join(t2, NULL);
    	pthread_join(t3, NULL);
    	pthread_join(t4, NULL);
	pthread_join(t5, NULL);
	pthread_join(t6, NULL);
	pthread_join(t7, NULL);
	pthread_join(t8, NULL);
    	pthread_join(t9, NULL);
	
	return 0;
}
