#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int solution_found(int*, int, int);
void descompunere(int, int*, int);
void print_array(int*, int, int);

int main(void) {
    puts("Introduceti numarul pe care doriti sa-l descompuneti.");
    int number; scanf("%d", &number);

    int aux = number, size_of_b = 0;
    while(aux > 0) {
        aux/=2;
        size_of_b ++;
    }

    int* B = (int*)calloc(size_of_b, sizeof(int));
    int term = 1;

    for(int i = 0; i<size_of_b; i++) {
        B[i] = term;
        term*=2;
    }

    descompunere(number, B, size_of_b);

    free(B); B = NULL;
    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

int solution_found(int* arr, int size, int result) {
    int sum = 0;
    for(int i = 0; i<size; i++) sum+=arr[i];
    return sum == result;
}

void print_array(int* arr, int size, int value) {
    for(int i = size-1; i>=0; i--) printf("%d%s", arr[i], i>0 ? " + " : " = ");
    printf("%d", value);
    return;
}

void descompunere(int value, int* base_arr, int size_of_base) {
    int sum = 0, l = 0;
    int* arr = (int*)calloc(size_of_base, sizeof(int));

    for(int i = size_of_base-1; i>=0;) {
        if(solution_found(arr, l, value) == 1) {
            print_array(arr, l, value);
            break;
        }

        if(sum + base_arr[i] <= value) {
            sum+=base_arr[i];
            arr[l++] = base_arr[i];
        } else i--;

    }

    free(arr); arr = NULL;
    return;
}