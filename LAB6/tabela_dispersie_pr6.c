#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FILE_ERROR  400
#define SENTINELA   INT_MIN
#define C1          1
#define C2          3

typedef struct _node { 
    int key, pos;
} LIST;

void    init_array(LIST*, int);
int     get_element(LIST*, int, int);
void    reduce_size(LIST*, int*);
int     find_element(LIST*, int, int);
void    insert_element(LIST*, int, int,int);

int     hash_function(int, int, int);

int main(void) {
    FILE* f_in  = fopen("date.txt", "r");
    FILE* f_out = fopen("date.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului.");
        return FILE_ERROR;
    }

    int size; fscanf(f_in, "%d", &size);

    LIST* array = (LIST*)calloc(size, sizeof(LIST));
    init_array(array, size);

    for(int i = 0, number; i<size; i++) {
        fscanf(f_in, "%d", &number);
        insert_element(array, size, number, i);
    } fclose(f_in);


    for(int i = 0; i<size; i++) {
        int number = get_element(array, size, i);
        if(number != SENTINELA) fprintf(f_out, "%d ", number);
    }
    fclose(f_out);

    free(array); array = NULL;
    return 0;
}

void init_array(LIST* arr, int size) {
    for(int i = 0; i<size; i++) {
        arr[i].key = SENTINELA;
        arr[i].pos = -1;
    }
}

int hash_function(int element, int incercare, int size) {
    return (incercare+element) % size;
}

int find_element(LIST* arr, int size, int element) {
    for(int i = 0; i<size; i++) {
        if(arr[i].key == element) return 1;
    }

    return 0;
}

void insert_element(LIST* arr, int size, int element, int index) {
    int incercare = 0;
    int plasat = 0;
    while(plasat == 0 && incercare <= size) {
        int location = hash_function(element, incercare, size);
        if(arr[location].key == SENTINELA) {
            arr[location].key = element;
            arr[location].pos = index;
            plasat = 1;
        } else {
            if(find_element(arr, size, element) == 0) {
                incercare++;
                continue;
            }
            else break;
        }
    }  
}

int get_element(LIST* arr, int size, int index) {
    for(int i = 0; i<size; i++) {
        if(arr[i].pos == index) return arr[i].key;
    }

    return SENTINELA;
}