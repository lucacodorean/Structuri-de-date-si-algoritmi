#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_ERROR      400
#define MAX_CHAR_IN_NAME 30

typedef struct {
    char* denumire_produs;
    int greutate, valoare;
    float densitate;
} PRODUS;

void sortare(PRODUS*, int);
void swap(PRODUS*, PRODUS*);
PRODUS* init_produs_array(FILE*, int);
void selecteaza_produse(PRODUS*, int, int, FILE*);

int main(void) {

    FILE* data_in = fopen("data.in", "r");
    FILE* data_out = fopen("data.out", "w");

    if(data_in == NULL || data_out == NULL) {
        perror("Eroare ");
        return FILE_ERROR;
    }

    int maximum_capacity; fscanf(data_in, "%d", &maximum_capacity);
    int produse_count;    fscanf(data_in, "%d", &produse_count);
    PRODUS* produse = init_produs_array(data_in, produse_count); fclose(data_in);

    sortare(produse, produse_count);
    selecteaza_produse(produse, produse_count, maximum_capacity, data_out); 
    for(int i = 0; i<produse_count; i++) {
        free(produse[i].denumire_produs);
    } free(produse); produse = NULL;

    fprintf(data_out, "Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    fclose(data_out);
    return 0;
}

void swap(PRODUS* first, PRODUS* second) {
    PRODUS temp = *first;
    *first = *second;
    *second = temp;
}

void sortare(PRODUS* produse, int size) {
    for(int i = 0; i<size-1; i++) {
        for(int j = i+1; j<size; j++) {
           if(produse[i].densitate < produse[j].densitate) swap(&produse[i], &produse[j]);
        }
    }
}

PRODUS* init_produs_array(FILE* path, int size) {  
    PRODUS* produse = (PRODUS*)calloc(size, sizeof(PRODUS));
    int len = 0;
    for(int i = 0; i<size; i++) produse[i].denumire_produs = (char*)calloc(MAX_CHAR_IN_NAME, sizeof(char));
    while(fscanf(path, "%s %d %d", produse[len].denumire_produs, &produse[len].greutate, &produse[len].valoare) == 3) {
        produse[len].densitate = (produse[len].valoare*1.0/produse[len].greutate);   
        len++;
    }
    return produse;
}

void selecteaza_produse(PRODUS* produse, int size, int maximum_capacity, FILE* path) {
    float current_capacity = 0;
    int profit = 0;
    for(int i = 0; i<size && maximum_capacity > 0; i++) {
        if(produse[i].greutate > maximum_capacity) {
            profit += maximum_capacity*produse[i].densitate;
            fprintf(path, "S-a selectat doar %0.3f din %s.\n", (float)(produse[i].greutate - maximum_capacity), produse[i].denumire_produs);
            current_capacity += ((float)(produse[i].greutate - maximum_capacity));
            maximum_capacity = 0;
        } else {
            current_capacity += produse[i].greutate;
            maximum_capacity -= produse[i].greutate;
            profit += produse[i].valoare; 
            fprintf(path, "S-a selectat %s in totalitate.\n", produse[i].denumire_produs);
        } 
    }

    fprintf(path, "Capacitatea totala selectata este: %0.3f. Profitul este: %d.\n\n", current_capacity, profit);
}