/*
 Implement the Pre-emptive priority scheduling algorithm. Take Process ID, Burst time, Arrival time, and Process Priority as inputs.
 Output the average waiting time, average response time and average turnaround times.
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
    int priority;
    int metCPUTime;
};

void displayProcessTable(struct PCB arr[], int size) {
    printf("Pr\tBu\tAr\tPr\n");
    
    for (int i = 0; i < size; i++) {
        printf("%d\t", arr[i].pid);
        printf("%d\t", arr[i].burstTime);
        printf("%d\t", arr[i].arrivalTime);
        printf("%d\t", arr[i].priority);
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
        int priority = arr[i].priority;
        int metCPUTime = arr[i].metCPUTime;
        
        while (pid < arr[j].pid && j != -1) {
            arr[j+1].pid = arr[j].pid;
            arr[j+1].burstTime = arr[j].burstTime;
            arr[j+1].arrivalTime = arr[j].arrivalTime;
            arr[j+1].priority = arr[j].priority;
            arr[j+1].metCPUTime = arr[j].metCPUTime;
            j--;
        }
        
        arr[j+1].pid = pid;
        arr[j+1].burstTime = burstTime;
        arr[j+1].arrivalTime = arrivalTime;
        arr[j+1].priority = priority;
        arr[j+1].metCPUTime = metCPUTime;
    }
}

void subset_burstTimeSort(struct PCB arr[], int size, int start, int end) {
    // Burst time - based sorting
    // Sort a subset
    // Insertion Sort
    for (int i = start + 1; i < end + 1; i++) {
        int j = i - 1;
        
        int pid = arr[i].pid;
        int burstTime = arr[i].burstTime;
        int arrivalTime = arr[i].arrivalTime;
        int priority = arr[i].priority;
        int metCPUTime = arr[i].metCPUTime;
        
        while (burstTime < arr[j].burstTime && j != -1) {
            arr[j+1].pid = arr[j].pid;
            arr[j+1].burstTime = arr[j].burstTime;
            arr[j+1].arrivalTime = arr[j].arrivalTime;
            arr[j+1].priority = arr[j].priority;
            arr[j+1].metCPUTime = arr[j].metCPUTime;
            j--;
        }
        
        arr[j+1].pid = pid;
        arr[j+1].burstTime = burstTime;
        arr[j+1].arrivalTime = arrivalTime;
        arr[j+1].priority = priority;
        arr[j+1].metCPUTime = metCPUTime;
    }
}

void subset_prioritySort(struct PCB arr[], int size, int start, int end) {
    // Priority - based sorting
    // Sort a subset
    // Insertion Sort
    for (int i = start + 1; i < end + 1; i++) {
        int j = i - 1;
        
        int pid = arr[i].pid;
        int burstTime = arr[i].burstTime;
        int arrivalTime = arr[i].arrivalTime;
        int priority = arr[i].priority;
        int metCPUTime = arr[i].metCPUTime;
        
        while (arr[i].priority < arr[j].priority && j != -1) {
            arr[i].pid = arr[j].pid;
            arr[i].burstTime = arr[j].burstTime;
            arr[i].arrivalTime = arr[j].arrivalTime;
            arr[i].priority = arr[j].priority;
            arr[i].metCPUTime = arr[j].metCPUTime;
            j--;
        }
        
        arr[j+1].pid = pid;
        arr[j+1].burstTime = burstTime;
        arr[j+1].arrivalTime = arrivalTime;
        arr[j+1].priority = priority;
        arr[j+1].metCPUTime = metCPUTime;
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
        int priority = arr[i].priority;
        int metCPUTime = arr[i].metCPUTime;
        
        while (arrivalTime < arr[j].arrivalTime && j > -1) {
            arr[j+1].pid = arr[j].pid;
            arr[j+1].burstTime = arr[j].burstTime;
            arr[j+1].arrivalTime = arr[j].arrivalTime;
            arr[j+1].priority = arr[j].priority;
            arr[i].metCPUTime = arr[j].metCPUTime;
            j--;
        }
        
        arr[j+1].pid = pid;
        arr[j+1].burstTime = burstTime;
        arr[j+1].arrivalTime = arrivalTime;
        arr[j+1].priority = priority;
        arr[j+1].metCPUTime = metCPUTime;
    }
}

void prioritySort(struct PCB arr[], int size) {
    // Priority - based Sort
    // Insertion Sort
    for (int i = 1; i < size; i++) {
        int j = i - 1;
        
        int pid = arr[i].pid;
        int burstTime = arr[i].burstTime;
        int arrivalTime = arr[i].arrivalTime;
        int priority = arr[i].priority;
        int metCPUTime = arr[i].metCPUTime;
        
        while (priority < arr[j].priority && j > -1) {
            arr[j+1].pid = arr[j].pid;
            arr[j+1].burstTime = arr[j].burstTime;
            arr[j+1].arrivalTime = arr[j].arrivalTime;
            arr[j+1].priority = arr[j].priority;
            arr[i].metCPUTime = arr[j].metCPUTime;
            
            j--;
        }
        
        arr[j+1].pid = pid;
        arr[j+1].burstTime = burstTime;
        arr[j+1].arrivalTime = arrivalTime;
        arr[j+1].priority = priority;
        arr[j+1].metCPUTime = metCPUTime;
    }
}

void priorityConflictSort(struct PCB arr[], int size, int algo) {
    // Sort processes with similar priority according to PID / Burst Time
    
    // algo: 1 = PID, 2 = Burst Time a.k.a. Shortest Job
    int start, end;
    int i = 1;
    
    while (i < size) {
        // Select subset with same priority
        start = i-1;
        while (arr[i].priority == arr[i-1].priority) {
            i++;
        }
        end = i-1;
        
        // Sort subset according to PID / Burst Time
        if (algo == 1) subset_pidSort(arr, end - start + 1, start, end);
        else if (algo == 2) subset_burstTimeSort(arr, end - start + 1, start, end);
        else return;
        
        i++;
    }
}

struct PCB * initQueue(int size) {
    struct PCB *queue = (struct PCB *) malloc(sizeof(struct PCB) * size);
    for (int i = 0; i < size; i++) {
        queue[i].pid = NONE;
        queue[i].arrivalTime = NONE;
        queue[i].burstTime = NONE;
        queue[i].priority = NONE;
        queue[i].metCPUTime = NONE;
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
            arr[i].priority = process.priority;
            arr[i].metCPUTime = process.metCPUTime;
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
        arr[i-1].priority = arr[i].priority;
        arr[i-1].metCPUTime = arr[i].metCPUTime;
    }
    
    arr[size - 1].pid = NONE;
    arr[size - 1].arrivalTime = NONE;
    arr[size - 1].burstTime = NONE;
    arr[size - 1].priority = NONE;
    arr[size - 1].metCPUTime = NONE;
    
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

int countProcesses(struct PCB arr[], int size) {
    int count = 0;
    for (int i = 0; i < size; i++)
        if (arr[i].pid != NONE) count++;
    
    return count;
}

int main() {
    printf("*** Pre-emptive Scheduling Algorithm - Priority Scheduling ***\n");
    // Note: Pre-emptive algorithms will stop a process, hence will context switch.
    
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
        
        printf("Enter priority: ");
        scanf("%d", &process[i].priority);
        
        process[i].metCPUTime = -1;
    }
    
    printf("\n** Input Table **\n");
    displayProcessTable(process, numOfProcesses);
    
    // Sort by arrival time
    printf("** Sorted by Arrival Time **\n");
    arrivalTimeSort(process, numOfProcesses);
    displayProcessTable(process, numOfProcesses);
    
    // Ready Queue
    struct PCB *readyQueue = initQueue(numOfProcesses);
    int r;
    
    // Clock Cycles
    int clk = 0;
    int p = 0;
    
    // Process running in CPU
    struct PCB running;
    running.pid = NONE;
    running.burstTime = -1;
    
    int waitingTime = 0;
    int turnaroundTime = 0;
    int responseTime = 0;
    
    printf("*** Gantt Chart ***\n");
    
    while (clk < 100) {
        // Add new processes to ready queue
        while (clk == process[p].arrivalTime && p < numOfProcesses) {
            enqueue(process[p], readyQueue, numOfProcesses);
            p++;
        }
        
        // Sort all processes in ready queue according to priority
        prioritySort(readyQueue, numOfProcesses);
        priorityConflictSort(readyQueue, numOfProcesses, 2);
        
        // If CPU time is over, clear process from CPU
        if (running.burstTime == 0) {
            running.pid = NONE;
            running.burstTime = NONE;
            
            // Calculation of Turnaround time = Time from Ready Queue to Termination
            turnaroundTime += clk - running.arrivalTime;
            // Assumption: Process is sent into Ready Queue immediately after it arrives.
        }
        
        // If no process is running in CPU & Processes are in Ready Queue,
        if (running.pid == NONE && !isEmpty(readyQueue, numOfProcesses)) {
            // Run highest priority process first
            running = dequeue(readyQueue, numOfProcesses);
            printf("%d - %d: P%d\n", clk, clk+1, running.pid);
            
            running.burstTime--;
        }
        
        // If process IS running in CPU & Processes are in Ready Queue,
        else if (running.pid != NONE && !isEmpty(readyQueue, numOfProcesses)) {
            // If process in front of ReadyQueue has more priority, or same priority with less burst time,
            if ((running.priority > (*readyQueue).priority) ||
                (running.priority == (*readyQueue).priority) && (running.burstTime > (*readyQueue).burstTime)) {
                // Swap running and ready processes
                struct PCB temp = running;
                running = *readyQueue;
                *readyQueue = temp;
            }
            
            printf("%d - %d: P%d\n", clk, clk+1, running.pid);
            running.burstTime--;
        }
        
        // If process IS running in CPU & Processes are NOT in Ready Queue,
        else if (running.pid != NONE && isEmpty(readyQueue, numOfProcesses)) {
            printf("%d - %d: P%d\n", clk, clk+1, running.pid);
            running.burstTime--;
        }
        else {
            // Do nothing
        }
        
        // Calculation of Waiting time
        waitingTime += countProcesses(readyQueue, numOfProcesses);
        
        // Calculation of Response time
        if (running.metCPUTime == -1) {
            running.metCPUTime = clk;
            responseTime += clk - running.arrivalTime;
        }
        
        clk++;
    }
    
    // Output: Average waiting, response, and turnaround times
    printf("\nAverage waiting time: %lf \n", ((double)waitingTime / numOfProcesses));
    printf("Average response time: %lf \n", ((double)responseTime / numOfProcesses));
    printf("Average turnaround time: %lf \n", ((double)turnaroundTime / numOfProcesses));
    
    return 0;
}

/*
 Assumption:
 Time to context switch (i.e.) switch Process Control Blocks [PCB] in & out of CPU is '0'.
 */
