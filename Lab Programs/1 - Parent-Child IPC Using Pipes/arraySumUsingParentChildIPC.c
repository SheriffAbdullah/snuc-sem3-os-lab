/*
 Assume an array of size n. The objective is to find the total sum of all elements of the array.
 Create a child process and split the array into two between parent and the child. Both the parent and the child calculate the partial sum of the array. Finally sum up the partial sums and find the total sum of the array. The parent and child should use pipes for IPC.
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    int N = 20;
    
    // Fill array
    int arr[N];
    for (int i = 0; i < N; i++) arr[i] = i + 1;
    
    int p, fd[2];
    p = pipe(fd);
    if (p < 0) printf("Error in pipe creation.");

    // Child
    if (fork() == 0) {
        int sum = 0;
        for (int i = N / 2; i < N; i++) sum += arr[i];
        
        // Note: USE a pointer - '&sum'
        write(fd[1], &sum, sizeof(sum));
    }
    // Parent
    else {
        int sum = 0;
        for (int i = 0; i < N / 2; i++) sum += arr[i];
        
        int childSum;
        read(fd[0], &childSum, sizeof(childSum));
        
        sum += childSum;
        
        printf("Sum of array is: %d\n", sum);
    }
    
    return 0;
}
