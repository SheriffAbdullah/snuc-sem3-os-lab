/*
 Solution to Deadlock -> Asymmetric Solution.
 (i.e.)
 If Philosopher is Odd-numbered  : Left, then Right Chopstick.
 If Philosopher is Even-numbered : Right, then Left Chopstick.
 */

#include <stdio.h>
#include <stdlib.h> // For 'rand()'
#include <unistd.h>  // For 'sleep()'
#include <semaphore.h>
#include <pthread.h>

#define PHILS 5
#define MEALS 2
#define WAIT_TIME 1    // Upper bound

// Semaphore
unsigned int chopstick[PHILS];

void semaphore_wait(int i) {
    while (chopstick[i] < 1); // Busy wait
    chopstick[i]--;
    return;
}

void semaphore_signal(int i) {
    chopstick[i]++;
    return;
}

// Simulating dining philosophers for 1 day (2 meals a day).
int belly[PHILS];

void philosopher(int i) {
    do {
        // Even-numbered phiosopher
        if (i % 2 == 0) {
            //printf("Philosopher %d: Waiting for RIGHT chopstick. \n", (i+1));
            semaphore_wait((i + 1) % PHILS);
            //printf("Philosopher %d: TOOK RIGHT chopstick. \n", (i+1));
            
            //printf("Philosopher %d: Waiting for LEFT chopstick. \n", (i+1));
            semaphore_wait(i);
            //printf("Philosopher %d: TOOK LEFT chopstick. \n", (i+1));
            
            // Eat
            printf("Philosopher %d: Eating. \n", (i + 1));
            sleep(rand() % WAIT_TIME);
            belly[i]--;    // Finished eating
            
            // Release Chopsticks
            semaphore_signal(i);
            //printf("Philosopher %d: RELEASED RIGHT chopstick. \n", (i+1));
            
            semaphore_signal((i + 1) % PHILS);
            //printf("Philosopher %d: RELEASED LEFT chopstick. \n", (i+1));
            
            // Think
            printf("Philosopher %d: Thinking. \n", (i + 1));
            sleep(rand() % WAIT_TIME);
        }
        // Odd-numbered philosopher
        else {
            // Picking up chopsticks
            //printf("Philosopher %d: Waiting for LEFT chopstick. \n", (i+1));
            semaphore_wait(i);
            //printf("Philosopher %d: TOOK LEFT chopstick. \n", (i+1));
            
            //printf("Philosopher %d: Waiting for RIGHT chopstick. \n", (i+1));
            semaphore_wait((i + 1) % PHILS);
            //printf("Philosopher %d: TOOK RIGHT chopstick. \n", (i+1));
            
            // Eat
            printf("Philosopher %d: Eating. \n", (i + 1));
            sleep(rand() % WAIT_TIME);
            belly[i]--;    // Finished eating
            
            // Release Chopsticks
            semaphore_signal((i + 1) % PHILS);
            //printf("Philosopher %d: RELEASED LEFT chopstick. \n", (i+1));
            
            semaphore_signal(i);
            //printf("Philosopher %d: RELEASED RIGHT chopstick. \n", (i+1));
            
            // Think
            printf("Philosopher %d: Thinking. \n", (i + 1));
            sleep(rand() % WAIT_TIME);
        }
        
        // STOP CONDITION:
        // If philosopher has eaten all meals,
        if (belly[i] <= 0) {
            printf("Philosopher %d: Ate %d meals. LEAVING. \n", (i + 1), MEALS);
            return; // Philosopher exits
        }
            
    } while (1);
}

int main() {
    // Initialize
    for (int i = 0; i < PHILS; i++) chopstick[i] = 1;
    for (int i = 0; i < PHILS; i++) belly[i] = MEALS;
    
    // Philosophers
    pthread_t p0, p1, p2, p3, p4;
    
    pthread_create(&p0, NULL, (void *)philosopher, (void *)0);
    pthread_create(&p1, NULL, (void *)philosopher, (void *)1);
    pthread_create(&p2, NULL, (void *)philosopher, (void *)2);
    pthread_create(&p3, NULL, (void *)philosopher, (void *)3);
    pthread_create(&p4, NULL, (void *)philosopher, (void *)4);
    
    pthread_join(p0, NULL);
    pthread_join(p1, NULL);
    pthread_join(p2, NULL);
    pthread_join(p3, NULL);
    pthread_join(p4, NULL);
    
    return 0;
}

/*
 Possible solutions to prevent Deadlock:
 
 (i) Allow at most 4 philosophers to be sitting simultaneously at the table.
 
 (ii) Allow a Philosopher to pick up chopsticks only if both chopsticks are available.
    To do this, the phiosopher must pick them up in a critical section.
 
 (iii) Use an asymmetric solution - that is,
    an odd-numbered philosopher picks up the left chopstick and then the right chopstick,
    whereas an even-numbered philosopher picks up the right chpstick and then the left chopstick.
 */
