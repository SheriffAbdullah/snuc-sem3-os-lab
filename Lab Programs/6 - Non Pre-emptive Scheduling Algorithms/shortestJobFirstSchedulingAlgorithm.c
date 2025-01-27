/*
 Implement the Shortest Job First scheduling algorithm. Take PCB Id, Burst time and Arrival time as inputs.
 */

#include <stdio.h>
#include <stdlib.h>

#define NONE 99999
#define NEWLINE printf("\n");

// Process Control Block
struct PCB {
    int pid;
    int burstTime;
    int arrivalTime;
};

void displayGanttChart(struct PCB arr[], int size) {
    // Output
    printf("*** Gantt Chart ***\n");
    
    int time = 0;
    for (int i = 0; i < size; i++) {
        
        printf("%d - %d\t-> P%d\n", time, time + arr[i].burstTime, arr[i].pid);
        time += arr[i].burstTime;
    }
}

void displayProcessTable(struct PCB arr[], int size) {
    printf("Pr\tBu\tAr\tPr\n");
    
    for (int i = 0; i < size; i++) {
        printf("%d\t", arr[i].pid);
        printf("%d\t", arr[i].burstTime);
        printf("%d\t", arr[i].arrivalTime);
        NEWLINE;
    }
    NEWLINE;
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

void burstTimeSort(struct PCB arr[], int size) {
    // Burst Time - based Sort
    // Insertion Sort
    for (int i = 1; i < size; i++) {
        int j = i - 1;
        
        int pid = arr[i].pid;
        int burstTime = arr[i].burstTime;
        int arrivalTime = arr[i].arrivalTime;
        
        while (burstTime < arr[j].burstTime && j > -1) {
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

void burstTimeConflictSort(struct PCB arr[], int size) {
    // Sort processes with similar burst time according to PID
    
    // algo: 1 = PID, 2 = Burst Time a.k.a. Shortest Job
    int start, end;
    int i = 1;
    
    while (i < size) {
        // Select subset with same burst time
        start = i-1;
        while (arr[i].burstTime == arr[i-1].burstTime) {
            i++;
        }
        end = i-1;
        
        // Sort subset according to PID
        subset_pidSort(arr, end - start + 1, start, end);

        i++;
    }
}

struct PCB * initQueue(int size) {
    struct PCB *queue = (struct PCB *) malloc(sizeof(struct PCB) * size);
    for (int i = 0; i < size; i++) {
        queue[i].pid = NONE;
        queue[i].arrivalTime = NONE;
        queue[i].burstTime = NONE;
    }
    
    return queue;
}

int enqueue(struct PCB process, struct PCB arr[], int size) {
    for (int i = 0; i < size; i++) {
        // If empty spot available,
        if (arr[i].pid == NONE) {
            arr[i].pid = process.pid;
            arr[i].arrivalTime = process.arrivalTime;
            arr[i].burstTime = process.burstTime;
            return 0;
        }
    }
    
    // No space in queue
    return -1;
}

// Shift all elements of the queue to the left once.
struct PCB dequeue(struct PCB arr[], int size) {
    struct PCB out = arr[0];
    
    for (int i = 1; i < size; i++) {
        // If not empty,
        arr[i-1].pid = arr[i].pid;
        arr[i-1].arrivalTime = arr[i].arrivalTime;
        arr[i-1].burstTime = arr[i].burstTime;
    }
    
    arr[size - 1].pid = NONE;
    arr[size - 1].arrivalTime = NONE;
    arr[size - 1].burstTime = NONE;
    
    return out;
}

int isEmpty(struct PCB arr[], int size) {
    for (int i = 0; i < size; i++) {
        if (arr[i].pid != NONE) {
            return 0;
        }
    }
    return 1;
}

int main() {
    printf("*** Non Pre-emptive Scheduling Algorithm - Priority Scheduling ***\n");
    // Note: Pre-emptive algorithms will NOT stop a process, hence will NOT context switch.
    
    // Input
    int numOfProcesses;
    printf("Enter number of processes: ");
    scanf("%d", &numOfProcesses);
    
    // Index: 0 - PID | 1 - Burst time | 2 - Arrival time | 3 - Priority
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
    
    // Sort by arrival time
    printf("** Sorted by Arrival Time **\n");
    arrivalTimeSort(process, numOfProcesses);
    displayProcessTable(process, numOfProcesses);
    
    // Output Queue
    struct PCB *outputQueue = initQueue(numOfProcesses);
    
    // Ready Queue
    struct PCB *readyQueue = initQueue(numOfProcesses);
    int r;
    
    // Clock Cycles
    int clk = 0;
    int p = 0;
    
    // Process running in CPU
    struct PCB running;
    running.pid = NONE;
    
    int tempBurst = -1;
    
    printf("*** Gantt Chart ***\n");
    
    while (clk < 100) {
        // Add new processes to ready queue
        while (clk == process[p].arrivalTime) {
            enqueue(process[p], readyQueue, numOfProcesses);
            p++;
        }
        
        // Sort all processes in ready queue according to burst time
        burstTimeSort(readyQueue, numOfProcesses);
        burstTimeConflictSort(readyQueue, numOfProcesses);
        
        // If CPU time is over, clear process from CPU
        if (tempBurst == clk) {
            running.pid = NONE;
        }
        
        // If no process is running in CPU & Processes are in Ready Queue,
        if (running.pid == NONE && !isEmpty(readyQueue, numOfProcesses)) {
            // Run shortest job first (i.e.) smallest burst time
            running = *readyQueue;
            tempBurst = clk + running.burstTime;
            enqueue(dequeue(readyQueue, numOfProcesses), outputQueue, numOfProcesses);
            printf("%d - %d -> P%d\n", clk, clk+running.burstTime, running.pid);
        }
        
        clk++;
    }
    
    return 0;
}
