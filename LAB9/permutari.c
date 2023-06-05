#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int complete(int, int);
int correct(int*, int);
void print_solution(int*, int);
void bt(int, int, int*);

int main(void) {
    int n = 5;
    int X[n];
    bt(0,n,X);
    return 0;
}

int complete(int k, int n) {
    return k == n;
}

int correct(int* solution, int k) {
    for(size_t i = 0; i<k; i++) {
        if(solution[i] == solution[k] || abs(k - i) == abs(solution[k] - solution[i])) {
            return 0;
        }
    }
    return 1;
}

void print_solution(int* arr, int size) {
    /*for(int i = 0; i<size; i++) {
        printf("%d ", arr[i]);
    } printf("\n");*/


    for(int i = 1; i<6; i++) {
        for(int j = 0; j<5; j++) {
            printf("%c ", arr[j] == i ? '*' : '-');
        } printf("\n");
    }
    printf("\n");
    printf("\n");
}

void bt(int k, int n, int* X) {
    if(complete(k,n) == 1) {
        print_solution(X,k);
        return; 
    }

    int ok = 1;
    for(size_t i = 1; i<=n; i++) {
        X[k] = i;
        ok = correct(X,k); /// verificam ca solutia partiala este corect
        if(ok) bt(k+1, n, X);
    }
}