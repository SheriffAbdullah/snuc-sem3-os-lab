#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int GSUM = 0;
pthread_t tid[5];

pthread_mutex_t myLock = PTHREAD_MUTEX_INITIALIZER;

struct param {
	int* arr;
	int size;
};

void add(struct param p) {
	int sum = 0;
	for (int i = 0; i < p.size; i++) {
		sum += p.arr[i];
	}
	
	pthread_mutex_lock(&myLock);
	GSUM += sum;
	pthread_mutex_unlock(&myLock);
}

int main() {
    int arrSize;
    printf("Enter array size: ");
    scanf("%d", &arrSize);
    
    int arr[arrSize];
    for (int i = 0; i < arrSize; i++) {
        printf("Enter element [%d]: ", i+1);
        scanf("%d", &arr[i]);
    }
    
    // Set initial size of arrays
    int indivArrSize = arrSize / 5;
    int arrSizes[5] = {indivArrSize};
  
    // Assumption: Arr size >= 5
    int remainingEltCount = arrSize % 5
    for (int i = 0; i < remainingEltCount; i++) {
        
    }
    
	return 0;
}
