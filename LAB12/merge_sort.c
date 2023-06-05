#include <stdio.h>
#include <stdlib.h>

void interclasare(int* first, int size_of_first, int* second, int size_of_second, int* dest) {
    int indice_st = 0, indice_dr = 0;
    int len = 0;
    for(len = 0; len<=size_of_first + size_of_second; len++) {
        dest[len] = (first[indice_st] < second[indice_dr] ? first[indice_st++] : second[indice_dr++]);
    }
    return;
}

void merge_sort(int arr[], int left, int right) {
    if(left >= right) return;

    int middle = (left+right)/2;
    merge_sort(arr, left, middle);
    merge_sort(arr, middle+1, right);

    int* dest = (int*)calloc(left+right, sizeof(int));
    interclasare(arr + left, middle - left + 1, arr + middle, right-middle + 1, dest);
    return;
}

int main(void) {
    int arr[] = {3,4,6,2,1,6,17,8};
    int size = sizeof(arr)/sizeof(int);
    merge_sort(arr,0, size);
    for(int i = 0; i<sizeof(arr)/sizeof(int); i++) printf("%d ", arr[i]);

    return 0;
}