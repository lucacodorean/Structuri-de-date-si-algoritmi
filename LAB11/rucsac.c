#include <stdio.h>
#include <stdlib.h>

int max(int, int);
int solve(int*, int*, int, int);

int main(void) {

    printf("%s", "Introduceti numarul de obiecte: ");
    int size_of_arrays; scanf("%d", &size_of_arrays);

    int* values  = (int*)calloc(size_of_arrays, sizeof(int));
    int* weights = (int*)calloc(size_of_arrays, sizeof(int));

    printf("Introduceti %d perechi de forma (valoare, greutate):\n", size_of_arrays);
    for(int i = 0; i<size_of_arrays; i++) scanf("%d %d", &values[i], &weights[i]);

    printf("%s", "Introduceti greutatea rucsacului: "); 
    int kapsack_capacity; scanf("%d", &kapsack_capacity);

    int result = solve(values, weights, size_of_arrays, kapsack_capacity);

    printf("G_max = %d", result);
    return 0;
}

int max(int first, int second) { return first < second ? second : first; }

int solve(int* values, int* weights, int size_of_arrays, int kapsack_capacity) {
    int* dp = (int*)calloc(kapsack_capacity + 1, sizeof(int));                  /// capacitati + 1
    int result = 0;                                                             

    for(int j = 0; j<size_of_arrays; j++) {
        for(int i = kapsack_capacity; i>=0; i--) {
            if(i < weights[j]) continue;                                        /// daca capacitatea rucsacului pt care verificam ii mai mica decat obiectu nu facem nmc 
                                                                                /// nu poti sa pui un elefant intr-o punga
            dp[i] = max(dp[i], dp[i-weights[j]] + values[j]);                   /// altfel, determinam greutatea maxima pe care o putem pune
        }

        for(int i = 0; i<kapsack_capacity+1; i++) printf("%d ", dp[i]);         
        printf("\n");
    }

    result = dp[kapsack_capacity];                                              /// rezultatul se afla pe pozitia capacitatii pe care o verificam.
    free(dp); dp = NULL;
    return result;
}