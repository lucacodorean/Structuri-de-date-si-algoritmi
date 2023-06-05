/**
 * @file problema2.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief Generati toate stringurile formate din primele k litere mici de lungime n
 * @version 0.1
 * @date 2023-05-02
 * 
 * @copyright Copyright (c) 2023
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int complete(int, int);
void print_solution(int*, char*, int);
void bt(int, int, int*, char*, int*);

int main(void) {
    int n, M;
    printf("Introduceti valori pentru n si M, in ordinea data: ");
    scanf("%d %d", &n, &M);

    int contor = 0;
    int X[n]; 
    char letters[M];

    for(int i = 0; i<M; i++) {
        letters[i] = (char)('a'+i);
    }

    bt(0,n,X, letters, &contor);

    printf("Exista %d permutari care respecta cerinta indicata.", contor);
    printf("\nCompiled in %0.3f seconds. ", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

int complete(int k, int n) {
    return k == n;
}

void print_solution(int* arr, char* letters, int size) {
    for(int i = 0; i<size; i++) {
        printf("%c", letters[arr[i]-1]);
    } printf("\n");
}

void bt(int k, int n, int* solution, char* letters, int* contor) {
    if(complete(k, n) == 1) {
        (*contor)++;
        print_solution(solution, letters, n);
        return;
    }
    
    for(int i = 1; i<=n; i++) {
        solution[k] = i;
        bt(k+1,n, solution, letters, contor);
    }
}