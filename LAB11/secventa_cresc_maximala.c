/**
 * @file secventa_cresc_maximala.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief Se cere sa se determine lungimea maxima a unui subsir ordonat crescator dintr-un sir de numere dat. 
 *        Strategie:
 *              Introducem numerele intr-un array. Facem verificari la fiecare pas.
 * @version 0.1
 * @date 2023-05-16
 * 
 * @copyright Copyright (c) 2023
 */

#include <stdio.h>
#include <stdlib.h>

void scrie(int*, int*, int, FILE*);
void solve(FILE*, FILE*, int);

#define FILE_ERROR 400

int main(void) {
    FILE* data_in = fopen("scmax.in", "r");
    FILE* data_out = fopen("scmax.out", "w");

    if(data_in == NULL || data_out == NULL) {
        perror("Error ");
        return FILE_ERROR;
    }

    int size; fscanf(data_in, "%d", &size);
    solve(data_in, data_out, size);

    fclose(data_in); fclose(data_out);
    return 0;
}

void scrie(int* p, int* arr, int x, FILE* path) {
    if(p[x] != -1) scrie(p, arr, p[x], path);
    fprintf(path, "%d ", arr[x]);
}


void solve(FILE* path_in, FILE* path_out, int size) {

    int* arr = (int*)calloc(size,sizeof(int));          /// retinem numerele
    int* dp  = (int*)calloc(size,sizeof(int));          /// dp[i] = lungimea celui mai lung subsir maximal care incepe pe pozitia i
    int* sol = (int*)calloc(size,sizeof(int));          /// retinem indicii unde s-au determinat valorile maxime     

    for(int i = 0; i<size; i++) sol[i] = -1;            /// marcam toate elementele din sol ca fiind egale cu -1, pentru ca s-ar putea ca secventa sa inceapa la index 0

    for(int i = 0; i<size; i++) {
        fscanf(path_in, "%d", &arr[i]);                 /// citimm elementele din fisier si le punem in array
        dp[i] = 1;                                      /// consideram ca elementul este maxim, deci lungimea subsirului maximal care incepe pe pozitia curenta e 1
        for(int j = 0; j<i; j++) {                      /// pentru elementele mai mici decat cel curent, pana la pozitia curenta, vom actualiza lungimea subsirului; 
            if(arr[i] > arr[j] && dp[i] < dp[j] + 1) {  /// dp[i] < dp[j] +1 asigura ca va fi sirul maximal, pt ca s-ar putea sa fie deja un sir gasit;
                dp[i] = dp[j] +1;                       /// crestem lungimea subsirului pentru elementul curent
                sol[i] = j;                             /// marcam locatia valorii maxime pana la pozitia curenta.
            }
        }
    }

    int imax = 0;                                       /// aici vom retine indexul la care incepe subsirul maximal.
    for(int i = 0; i<size; i++) {                       /// in acest for se va determina indexul
        if(dp[i] > dp[imax]) {
            imax = i;
        }
    }

    fprintf(path_out, "%d\n", dp[imax]);                /// afisam lungimea subsirului maximal crescator
    scrie(sol, arr, imax, path_out);                    /// vom afisa, elementele care-l formeaza

    free(arr);  arr = NULL;                             /// eliberam memoria pentru numere
    free(dp);   dp = NULL;                              /// eliberam memoria pentru dp
    free(sol);  sol = NULL;                             /// eliberam memoria pentru solutie
}