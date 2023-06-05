#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_MAX 25

typedef struct _placeholder {
    char denumire_produs[25];
    int greutate, valoarea;
    float densitate;
} PRODUCT;

typedef int RUCSAC;

PRODUCT* new_product(char*, int, int);
void     init_produse(FILE*, PRODUCT*, int);
void     sort(PRODUCT*, int);                   /// pentru ca strategia greedy sa functioneze, trebuie sa sortam dupa densitatea produselor.
void     greedy(PRODUCT*, int, RUCSAC);

int main(void) {

    FILE* in = fopen("data.in", "r");
    FILE* out = fopen("data.out", "w");

    RUCSAC capacitate_maxima; fscanf(in, "%d", &capacitate_maxima);
    int    numar_produse;     fscanf(in, "%d", &numar_produse);

    PRODUCT* produse = (PRODUCT*)calloc(numar_produse, sizeof(PRODUCT));
    init_produse(in, produse, numar_produse);   fclose(in);

    sort(produse, numar_produse);
    greedy(produse, numar_produse, capacitate_maxima);

    free(produse);
    return 0;
}

void init_produse(FILE* in, PRODUCT* produse, int numar_produse) {
    for(int i = 0, height, value; i<numar_produse; i++) {
        fscanf(in, "%s %d %d", produse[i].denumire_produs, &height, &value);

        produse[i].greutate  = height;
        produse[i].valoarea  = value;
        produse[i].densitate = (produse[i].valoarea*1.0)/ produse[i].greutate;
    }
}

void sort(PRODUCT* produse, int size) {
    for(int i = 0; i<size-1; i++) {
        for(int j = i+1; j<size; j++) {
            if(produse[i].densitate < produse[j].densitate) {
                PRODUCT temp = produse[i];
                produse[i] = produse[j];
                produse[j] = temp;
            }
        }
    }
}

void greedy(PRODUCT* produse, int size, RUCSAC maximum_capacity) {
    float result = 0;

    for(int i = 0; i<size && maximum_capacity != 0; i++) {
        if(produse[i].greutate > maximum_capacity) {
            result += (float)(maximum_capacity*produse[i].densitate);
            maximum_capacity = 0;
        } else {
            result += produse[i].valoarea;
            maximum_capacity -= produse[i].greutate;
        }
    }

    printf("\nProfitul este de: %f", result);
}