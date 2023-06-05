#include <stdio.h>
#include <stdlib.h>

void greedy(int,int,int*);

int main(void) {

    int number;
    scanf("%d", &number);

    int cate = 0;
    int aux = number;
    while(aux>0) {
        cate++;
        aux/=2;
    }

    int* powers_of_2 = (int*)calloc(cate,sizeof(int));
    aux = 1;
    for(int i = 0; i<cate; i++) {
        powers_of_2[i] = aux;
        aux*=2;
    }

    greedy(number, cate, powers_of_2);

    return 0;
}

void greedy(int number, int size, int* powers_of_2) {
    int result = number;

    for(int i = size-1; i>=0; ) {
        if(result - powers_of_2[i] >= 0) {
            printf("%d ", powers_of_2[i]);
            result = result - powers_of_2[i];
        }
        else i--; 
    }

    return;
}