/**
 * @file subiect_1_2.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */


#include <stdio.h>
#include <stdlib.h>

void sort(int*, int);
int greedy(int*, int, int);

int main(void) {
    int L = 6, len = 3;
    int arr[3] = {1,4,1};

    int result = greedy(arr,len,L);
    printf("%d", result);

    return 0;
}

void sort(int* arr, int size) {
    for(int i = 0; i<size-1; i++) {
        for(int j = i+1; j<size; j++) {
            if(arr[i] > arr[j]) {
                int temp = arr[j];
                arr[j] = arr[i];
                arr[i] = temp;
            }
        }
    }
}

int greedy(int* arr, int size, int L) {

/*
    1 1 3 4 => 2
    2 3 4   => 2 + 2 + 3 = 7
    5 4     => 7 + 9     = 16 

    1 1 4   => 2
    2 4     => 2 2 4 = 8

    3 1 4 1  => result = 2
    2 3 4    => result = 2 + 2 + 3 = 7
    5 4      => result = 7 + 5 + 4 = 16
    9        => am ajuns la L
*/  
int result = 0;
    for(int desc_min = 0; size > 1 && result != L;) {
        sort(arr,size);                                         /// ne asiguram ca in arr[0] si arr[1] avem valorile minime mereu
        desc_min = arr[0] + arr[1];                             /// unim bucatile minime
        result += desc_min;                                     /// adaugam costul lor in rezultat
        arr[size++] = desc_min;                                 /// pe ultima pozitie din array punem arr[0]+arr[1];
        for(int k = 0; k<2; k++) {                              /// stergem primele doua elemente din array, adica pe cele minime
            for(int j = 0; j<=size-1; j++) arr[j] = arr[j+1];
            size--;
        }
    }
    return result;
}