/*
 Implement the banker’s algorithm.
 a. Input: Process, allocated, max needed, and total number of different resources available.
 b. Output: A safe sequence of processes.
*/

#include <stdio.h>
#include <stdbool.h>

int array_sum(int *arr, int len) {
    int sum = 0;
    for (int i = 0; i < len; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    /*
     int numOfPro;
     printf("Enter number of processes: ");
     scanf("%d", &numOfPro);
     
     int numOfRes;
     printf("Enter number of resources: ");
     scanf("%d", &numOfRes);
     
     int totalRes[numOfRes];
     printf("\n*** Total Instances of each Resource *** \n");
     for (int i = 0; i < numOfRes; i++) {
        char c = i + 65;
        printf("%c: ", c);
        scanf("%d", &totalRes[i]);
     }
     
     int alloc[numOfPro][numOfRes];
     printf("\n*** Resources Allocated *** \n");
     for (int i = 0; i < numOfPro; i++) {
        for (int j = 0; j < numOfRes; j++) {
            char c = j + 65;
            printf("Process [%d] Resource [%c]: ", i, c);
            scanf("%d", &alloc[i][j]);
        }
     }
     
     int maxNeed[numOfPro][numOfRes];
     printf("\n*** Maximum Resources Needed *** \n");
     for (int i = 0; i < numOfPro; i++) {
        for (int j = 0; j < numOfRes; j++) {
            char c = j + 65;
            printf("Process [%d] Resource [%c]: ", i, c);
            scanf("%d", &maxNeed[i][j]);
        }
     }
     */
    
    // TEST INPUT STUB START
    int numOfPro = 5;
    int numOfRes = 3;
    
    int totalRes[3] = {10, 5, 7};
    int alloc[5][3] = {{0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};
    int maxNeed[5][3] = {{7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
    // TEST INPUT STUB END
    
    // Number of available instances of each Resource
    int available[numOfRes];
    for (int i = 0; i < numOfRes; i++) {
        int sum = 0;
        for (int j = 0; j < numOfPro; j++) {
            sum += alloc[j][i];
        }
        available[i] = totalRes[i] - sum;
    }
    
    // Number of instances of each Resource needed by process to execute
    int need[numOfPro][numOfRes];
    for (int i = 0; i < numOfPro; i++) {
        for (int j = 0; j < numOfRes; j++) {
            need[i][j] = maxNeed[i][j] - alloc[i][j];
        }
    }
    
    // To keep track of executed processes
    int allocDone[numOfPro];
    for (int i = 0; i < numOfPro; i++) allocDone[i] = 0;
    
    // To keep track of sequence
    int seq[numOfPro];
    
    int ctr = 0;
    int flag_main;
    // Until unexecuted processes remain,
    while (array_sum(allocDone, numOfPro) != numOfPro) {
        // Check for deadlock
        
        // Processes with requested resources < available resources in each instance
        int allocPossible[numOfPro];
        for (int i = 0; i < numOfPro; i++) {
            int flag = 0;
            for (int j = 0; j < numOfRes; j++) {
                // If required resources > available resources in an instance,
                if (need[i][j] > available[j]) {
                    // Cannot execute process
                    flag = 1;
                }
            }
            
            if (flag == 1) allocPossible[i] = 0;
            else allocPossible[i] = 1;
        }
        
        // Deadlocked - None of the processes can be executed
        if (array_sum(allocPossible, numOfPro) == 0) {
            flag_main = 1;
            break;
        }
        // NO Deadlock - Find Safe Sequence
        else {
            for (int i = 0; i < numOfPro; i++) {
                // If process can be executed is yet to be executed,
                if (allocPossible[i] == true && allocDone[i] == false) {
                    // Allocate resources to process
                    
                    // Update safe sequence
                    seq[ctr++] = i;
                    
                    // Process returned resources after using.
                    for (int j = 0; j < numOfRes; j++) {
                        available[j] += need[i][j];
                    }
                    
                    allocDone[i] = true;
                }
            }
        }
    }
    
    // OUTPUT
    if (flag_main == 1) {
        printf("DEADLOCKED.\n");
    } else {
        printf("*** SAFE SEQUENCE ***\n");
        for (int i = 0; i < numOfPro - 1; i++) printf(" P%d ->", seq[i]);
        printf(" P%d. \n", seq[numOfPro - 1]);
    }
    
    return 0;
}
