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

void sortare(PRODUS*, int, char*);
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



    fputs("Varianta sortarii dupa valoarea produselor:\n", data_out);
    sortare(produse, produse_count, "valoare");
    selecteaza_produse(produse, produse_count, maximum_capacity, data_out);

    fputs("Varianta sortarii dupa greutatea produselor:\n", data_out);
    sortare(produse, produse_count, "greutate");
    selecteaza_produse(produse, produse_count, maximum_capacity, data_out); 

    fputs("Varianta sortarii dupa densitatea produselor:\n", data_out);
    sortare(produse, produse_count, "densitate");
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

void sortare(PRODUS* produse, int size, char* criteriu) {
    for(int i = 0; i<size-1; i++) {
        for(int j = i+1; j<size; j++) {
            if(strcmp("valoare", criteriu) == 0) {
                if(produse[i].valoare < produse[j].valoare) {
                    swap(&produse[i], &produse[j]);
                }
                continue;
            } else if (strcmp("greutate", criteriu) == 0) {
                if(produse[i].greutate < produse[j].greutate) {
                    swap(&produse[i], &produse[j]);
                }
                continue;
            } else if (strcmp("densitate", criteriu) == 0) {
                if(produse[i].densitate < produse[j].densitate) {
                    swap(&produse[i], &produse[j]);
                }
                continue;
            } else {
                printf("Eroare: Criteriu necunoscut.");
                return;
            }
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
    int current_capacity = 0, profit = 0;
    for(int i = 0; i<size && maximum_capacity > 0; i++) {
        if(produse[i].greutate <= maximum_capacity) {
            current_capacity+=produse[i].greutate;
            maximum_capacity-=produse[i].greutate;
            profit+=produse[i].valoare;
            fprintf(path, "S-a selectat produsul %s.\n", produse[i].denumire_produs);
        }
    }

    fprintf(path, "Capacitatea totala selectata este: %d. Profitul este: %d.\n\n", current_capacity, profit);
}