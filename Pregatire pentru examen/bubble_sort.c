#include <stdio.h>

void bubble_sort(int* arr, int size) {
    int sorted = 0;
    int aux = size;
    do {
        sorted = 0;
        for(int i = 0; i<=aux-1; i++) {
            if(arr[i] > arr[i+1]) {
                int temp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = temp;
                sorted = 1;
            }
        }

        aux--;

        for(int i = 0; i<size; i++) {
            printf("%d ", arr[i]);
        } printf("\n");

    } while(sorted);
}

/*
    Se observa ca la fiecare pas, algoritmul de Bubble Sort ne va reda, pe pozitia size-ului pentru care se face sortarea, elementul potrivit pozitiei.
*/

int main(void) {

    int arr[10] = {10,3,2,9,10,5,1,4,3,10};
    int n = sizeof(arr)/sizeof(int);
    bubble_sort(arr, n);

    return 0;
}