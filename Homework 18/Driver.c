#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define SIZE 100
#define MAX_THREAD 4

void mergeSort(int * arr, int size, int low, int high);
void mergeHelper(int * arr, int size, int low, int mid, int high);
void printArray(int * arr, int size);
void * pthreadMergeSort(void *);

int main() {
    srand(time(0));
    int inArr[SIZE];
    for(int i = 0; i < SIZE; i++) {
        inArr[i] = rand() % 10;
    }
    printArray(inArr, SIZE);
    printf("\n");

    mergeSort(inArr, SIZE, 0, SIZE-1);
    printArray(inArr, SIZE);
}

void mergeSort(int * arr, int size,  int low, int high) {
    int mid = 0;
    if (low < high) {
        mid = (low+high) / 2;

        mergeSort(arr, size, low, mid); //call itself for left partition
        mergeSort(arr, size, mid+1, high); //call itself for right portion

        //merge left and right partition in sorted order
        mergeHelper(arr, size, low, mid, high);
    }
}

void mergeHelper(int * arr, int size, int low, int mid, int high) {
    int outArray[size]; //create array for output
    int outSize = high - low + 1;

    int mergePos = 0;
    int left = low;
    int right = mid+1;

    //look for smallest element between partitions
    while(left <= mid && right <= high) {
        if(arr[left] <= arr[right]) {
            outArray[mergePos] = arr[left];
            left++;
        } else {
            outArray[mergePos] = arr[right];
            right++;
        }
        mergePos++;
    }

    //dump the remaining left partiiton
    while(left <= mid) {
        outArray[mergePos] = outArray[left];
        left++;
        mergePos++;
    }

    //dump the remaining right portion
    while(right <= high) {
        outArray[mergePos] = outArray[right];
	    right++;
	    mergePos++;
    }

    //replace the original array's contents with the merged
    for (mergePos = 0; mergePos < outSize; mergePos++) {
	         arr[low + mergePos] = outArray[mergePos];
	      }

}

void printArray(int * arr, int size) {
    printf("\n");
    char output[size * 2];
    for(int i = 0; i < size -1; i++) {
            output[i * 2] = (arr[i] + 48); //converts ints to chars
            output[i * 2 + 1] = ' ';
        }
    printf("%s\n", output);
}


