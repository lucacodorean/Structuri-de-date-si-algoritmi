/**
 * @file problema1.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief Toate permutarile lui n in care suma fiecarei perechi de elemente consecutive este <= M
 * @version 0.1
 * @date 2023-05-02
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int correct(int*, int, int);
int complete(int, int);
void print_solution(int*, int);
void bt(int, int, int, int*, int*);

int main(void) {
    int n,M;
    printf("Introduceti valori pentru n si M, in ordinea data: ");
    scanf("%d %d", &n, &M);

    int contor = 0;
    int X[n]; bt(0,n,M,X, &contor);

    printf("Exista %d permutari care respecta cerinta indicata.", contor);
    printf("\nCompiled in %0.3f seconds. ", clock()*1.0/CLOCKS_PER_SEC);

    return 0;
}

int complete(int k, int n) {
    return k == n;
}

int correct(int* solution, int size, int limit) {
    for(int i = 0; i<size; i++) {
        if(solution[i] + solution[i+1] > limit || solution[i] == solution[size]) {
            return 0;
        }
    }
    return 1;
}

void print_solution(int* arr, int size) {
    for(int i = 0; i<size; i++) {
        printf("%d ", arr[i]);
    } printf("\n");
}

void bt(int k, int n, int M, int* solution, int* contor) {
    if(complete(k,n) == 1) {
        (*contor)++;
        print_solution(solution, n);
        return;
    }

    int ok = 1;
    for(int i = 1; i<=n; i++) {
        solution[k] = i;

        ok = correct(solution, k, M);
        if(ok) {
            bt(k+1, n, M, solution, contor);
        }
    }
}