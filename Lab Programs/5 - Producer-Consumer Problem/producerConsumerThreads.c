#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdbool.h>

#define MAX_SIZE 2

// Bounded buffer
int stack[MAX_SIZE];

int count = 0;

pthread_mutex_t myLock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_prod = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_cons = PTHREAD_COND_INITIALIZER;

void producer(int prod) {
	pthread_mutex_lock(&myLock);
    
	for (int i = 0; i < 4; i++) {
        if (count > MAX_SIZE) exit(1);    /* overflow */
    		
        while (count == MAX_SIZE) {
            // Wait for 'cond1' to be fulfilled ('cond1' is NOT a specified condition. It is a signal).
            pthread_cond_wait(&cond_prod, &myLock);
        }
        
		// Free to write
		stack[count] = prod;
        count++;
	    	
        // Signal to 'cond2', Producer has produced. Consumer need not wait. Go ahead and consume.
        pthread_cond_signal(&cond_cons);
    
        printf("#%d produced.\n", prod); fflush(stdout);
	    	
		// sleep((rand() % 10));
    }
    
    pthread_mutex_unlock(&myLock);
}

void consumer(int cons) {
	pthread_mutex_lock(&myLock);
    	while (true) {
    		if (count < 0) exit(1);    /* underflow */
    		
    		while (count == 0) {
    			// Wait for 'cond2' to be fulfilled ('cond2' is NOT a specified condition. It is a signal from Producer, when it has produced content).
	    		pthread_cond_wait(&cond_cons, &myLock);
	    		// Note: Lock on 'count' is released while waiting.
    		}

		count--;
		
		// Content to read = Available
		printf("Consumer #%d consumed #%d\n", cons, stack[count]); fflush(stdout);
		
		// Signal to 'cond1', Consumer has consumed. Producer need not wait (thinking queue is full). Go ahead and produce.
		pthread_cond_signal(&cond_prod);
		
	}
	pthread_mutex_unlock(&myLock);
}

int main() {
	// Producers
	pthread_t t0, t1, t2, t3, t4;
	// Consumers
	pthread_t t5, t6, t7, t8, t9;
	
	pthread_create(&t5, NULL, (void *)consumer, (void *)0);
	pthread_create(&t6, NULL, (void *)consumer, (void *)1);
	pthread_create(&t7, NULL, (void *)consumer, (void *)2);
	pthread_create(&t8, NULL, (void *)consumer, (void *)3);
	pthread_create(&t9, NULL, (void *)consumer, (void *)4);
	
	pthread_create(&t0, NULL, (void *)producer, (void *)0);
	pthread_create(&t1, NULL, (void *)producer, (void *)1);
	pthread_create(&t3, NULL, (void *)producer, (void *)3);
	pthread_create(&t2, NULL, (void *)producer, (void *)2);
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
