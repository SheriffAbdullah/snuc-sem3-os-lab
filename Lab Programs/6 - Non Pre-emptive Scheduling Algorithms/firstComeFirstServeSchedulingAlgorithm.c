/*
 Implement the FCFS scheduling algorithm. Take PCB Id, Burst time and Arrival time as inputs.
 
 Assumption: Smaller PID = Higher Priority
 */

#include <stdio.h>
#include <stdbool.h>

#define NEWLINE printf("\n");

struct PCB {
    int pid;
    int burstTime;
    int arrivalTime;
};

void displayGanttChart(struct PCB arr[], int size) {
    // Output
    printf("*** Gantt Chart ***\n");
    int timeT = 0;
    int p = 0;
    while (timeT < 100) {
        if (timeT >= arr[p].arrivalTime) {
            printf("%d - %d\t-> P%d\n", timeT, timeT + arr[p].burstTime, arr[p].pid);
            timeT += arr[p].burstTime;
            p++;
        } else {
            timeT++;
        }
    }
}

void displayProcessTable(struct PCB arr[], int size) {
    printf("PID\tBu\tAr\n");
    
    for (int i = 0; i < size; i++) {
        printf("%d\t", arr[i].pid);
        printf("%d\t", arr[i].burstTime);
        printf("%d\t", arr[i].arrivalTime);
        NEWLINE;
    }
    NEWLINE;
}

void arrivalTimeSort(struct PCB arr[], int size) {
    // Arrival Time - based Sort
    // Insertion Sort
    for (int i = 1; i < size; i++) {
        int j = i - 1;
        
        int pid = arr[i].pid;
        int burstTime = arr[i].burstTime;
        int arrivalTime = arr[i].arrivalTime;
        
        while (arrivalTime < arr[j].arrivalTime && j > -1) {
            arr[j+1].pid = arr[j].pid;
            arr[j+1].burstTime = arr[j].burstTime;
            arr[j+1].arrivalTime = arr[j].arrivalTime;
            j--;
        }
        
        arr[j+1].pid = pid;
        arr[j+1].burstTime = burstTime;
        arr[j+1].arrivalTime = arrivalTime;
    }
}

void subset_pidSort(struct PCB arr[], int size, int start, int end) {
    // PCB ID - based sorting
    // Sort a subset
    // Insertion Sort
    for (int i = start + 1; i < end + 1; i++) {
        int j = i - 1;
        
        int pid = arr[i].pid;
        int burstTime = arr[i].burstTime;
        int arrivalTime = arr[i].arrivalTime;
        
        while (pid < arr[j].pid && j != -1) {
            arr[j+1].pid = arr[j].pid;
            arr[j+1].burstTime = arr[j].burstTime;
            arr[j+1].arrivalTime = arr[j].arrivalTime;
            j--;
        }
        
        arr[j+1].pid = pid;
        arr[j+1].burstTime = burstTime;
        arr[j+1].arrivalTime = arrivalTime;
    }
}

void arrivalConflictSort(struct PCB arr[], int size) {
    int start, end;
    int i = 1;
    
    // Processes w/ similar arrival time -> sort according to algorithm - FCFS [w/ PID Sort]
    while (i < size) {
        start = i-1;
        while (arr[i].arrivalTime == arr[i-1].arrivalTime) {
            i++;
        }
        end = i-1;
        
        subset_pidSort(arr, end - start + 1, start, end);
        
        i++;
    }
}

int main() {
    // Note: Assume No priority (or) SAME priority processes.
    printf("*** Non Pre-emptive Scheduling Algorithm - FCFS ***\n");
    // Note: Pre-emptive algorithms will NOT stop a process, hence will NOT context switch.
    
    int numOfProcesses;
    printf("Enter number of processes: ");
    scanf("%d", &numOfProcesses);
    
    // Index: 0 - PCB ID | 1 - Burst time | 2 - Arrival time
    struct PCB process[numOfProcesses];
    
    // Input process details
    for (int i = 0; i < numOfProcesses; i++) {
        printf("\nEnter process ID: ");
        scanf("%d", &process[i].pid);
        
        printf("Enter burst time: ");
        scanf("%d", &process[i].burstTime);
        
        printf("Enter arrival time: ");
        scanf("%d", &process[i].arrivalTime);
    }
    
    printf("\n** Input Table **\n");
    displayProcessTable(process, numOfProcesses);
    
    arrivalTimeSort(process, numOfProcesses);
    printf("** Sorted by Arrival Time **\n");
    displayProcessTable(process, numOfProcesses);
    
    // Processes w/ similar arrival time, sort according to PID
    arrivalConflictSort(process, numOfProcesses);
    printf("** Sorted by Arrival Time, and PID if conflict exists **\n");
    displayProcessTable(process, numOfProcesses);
    
    // Output
    displayGanttChart(process, numOfProcesses);
    
    return 0;
}

/*
 Note:
 -> ALWAYS Have Sample i/p and Expected o/p to reduce i/o testing time.
 */
