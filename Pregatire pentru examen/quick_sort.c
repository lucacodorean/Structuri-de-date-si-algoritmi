#include <stdio.h>
#include <stdlib.h>

int partition(int* arr, int low, int high) {
    int pivot = arr[high], sm = low-1;
    for(int i = low; i<high; i++) {
        if(arr[i] <= pivot) {
            sm++;
            int temp = arr[i];
            arr[i] = arr[sm];
            arr[sm] = temp;
        }
    }

    int temp = arr[high];
    arr[high] = arr[sm+1];
    arr[sm+1] = temp;
    return sm+1;
}


int main(void) {
    int A[8] ={-1,110, 9, 35, 14, 2, 5, 100};
    int size_of_A = sizeof(A)/sizeof(int);
    int ok = partition(A,1,7);

    for(int i = 0; i<size_of_A; i++) printf("%d ", A[i]);
    return 0;
}