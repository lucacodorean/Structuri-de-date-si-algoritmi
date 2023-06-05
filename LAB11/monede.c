#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int min(int first, int second) {return first < second ? first : second; }

int combinatii(int, int*, int);
int minim_bancnote(int, int*, int);

int main(void) {
    puts("Introduceti suma pe care doriti sa o descompuneti in bancnote.");
    int sum; scanf("%d", &sum);

    int arr[3] = {1,2,5};
    int size_of_arr = 3;

    printf("Suma %d se poate descompune in %d bancnote.", sum, minim_bancnote(sum, arr, size_of_arr));
    printf("\nSuma %d se poate obinte in %d moduri.", sum, combinatii(sum, arr, size_of_arr));
    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

int minim_bancnote(int sum, int* arr, int size_of_arr) {
    int* dp = (int*)calloc(sum+1, sizeof(int));        

    int INF = sum+1, result = 0;                            // setam o valoare sentinela

    dp[0] = 0;                                              // stabilim ca suma 0 nu se poate obtine cu un numar de bancnote
    for(int i = 1; i<sum+1; i++) dp[i] = INF;               // restul sumelor se pot obtine folosind bancnote

    for(int j = 0; j<size_of_arr; j++) {                    // prelucram fiecare bancnota pe rand
         for(int i = 1; i<sum+1; i++) {                     // pentru fiecare suma pana la suma ceruta
            if(i < arr[j]) continue;                        // daca suma curenta ii mai mica decat bacnota curenta nu o modificam, pentru ca nu putem obtine
                                                            // de exemplu 4 lei folosind o bancnota de 5 lei
            else dp[i] = min(dp[i], dp[i-arr[j]]+1);        // actualizam numarul de bancnote folosit pentru a obtine suma curenta
        }
    }

    result = dp[sum];                                       // numarul de bancnote necesar sumei transmise ca si parametru se afla pe pozitia dp[i]
    free(dp); dp = NULL;

    return result;
}

int combinatii(int sum, int* arr, int size_of_arr) {
    int* dp = (int*)calloc(sum+1, sizeof(int));
    int result = 0;

    dp[0] = 1;

    for(int j = 0; j<size_of_arr; j++) {
        for(int i = 1; i<sum+1; i++) {
            if(i<arr[j]) continue;
            dp[i] += dp[i-arr[j]];
        }
    }

    result = dp[sum];
    free(dp); dp = NULL;

    return result;
}