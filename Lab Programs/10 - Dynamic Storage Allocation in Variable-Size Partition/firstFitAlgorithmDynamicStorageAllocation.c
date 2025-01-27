#include <stdio.h>

int main() {
    /*
     int parts;
     printf("Enter number of partitions: ");
     scanf("%d", &parts);
     
     int partSize[parts];
     for (int i = 0; i < parts; i++) {
     printf("Enter size of partion [%d]: ", i);
     scanf("%d", &partSize[i]);
     }
     
     int pros;
     printf("Enter number of processes: ");
     scanf("%d", &pros);
     
     int proSize[pros];
     for (int i = 0; i < pros; i++) {
     printf("Enter size of process [%d]: ", i);
     scanf("%d", &proSize[i]);
     }
     */
    
    // TEST INPUT STUB START
    int parts = 6;
    int partSize[] = {200, 400, 600, 500, 300, 250};
    int pros = 4;
    int proSize[] = {357, 210, 468, 491};
    // TEST INPUT STUB END
    
    int partFilled[parts];
    for (int i = 0; i < parts; i++) partFilled[i] = 0;
    
    // '-1' if NOT Allocated
    // Otherwise, partition number
    int proStatus[pros];
    for (int i = 0; i < pros; i++) proStatus[i] = -1;
    
    // For every process,
    for (int i = 0; i < pros; i++) {
        // Check first space large enough to fit process
        for (int j = 0; j < parts; j++) {
            if (proSize[i] < partSize[j] && partFilled[j] == 0) {
                // Fill space with process
                partFilled[j] = 1;
                proStatus[i] = j;
                break;
            }
        }
    }
    
    // OUTPUT
    printf("Process | Partition\n");
    printf("-------------------\n");
    
    for (int i = 0; i < pros; i++) {
        if (proStatus[i] == -1) printf(" %d \t| NOT ALLOCATED\n", i);
        else printf(" %d \t| %d\n", i, proStatus[i]);
    }
    
    return 0;
}
