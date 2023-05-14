/**
 * @file lab.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief greedy
 *      - ofera nu o solutie, nu neaparat cea optima.
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int greedy(int*, int, int);

int main(void) {
    int currency[7] = {1,5,10,50,100,200,500};
    int size = 7;

    int requested_value;
    printf("Introduceti valoarea pe care doriti sa o extrageti de la bancomat: "); scanf("%d", &requested_value);
    int ok = greedy(currency, size, requested_value);
    
    if(ok) printf("Bancomatul returneaza suma, folosind %d bancnote.", ok);
    else printf("Bancomatul nu poate determina suma ceruta.");

    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

int greedy(int* arr, int size, int requested_value) {
    int contor = 0;

    for(int i = size-1; i>=0;) {
        if(requested_value >= arr[i]) {
            int aux = requested_value / arr[i];
            requested_value -= arr[i];
            printf("SELECTED-CURRENCY: %d \tREMAINING VALUE: %d.\n", arr[i], requested_value);
            contor++;
        } else i--;
    }



    return requested_value == 0 ? contor : 0;
}