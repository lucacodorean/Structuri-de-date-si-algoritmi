#include <stdlib.h>
#include <stdio.h>

#define MODULO 7
#define SENTINELA -9999999

typedef struct _node {
    int key;
} NODE;

NODE* create_node(int);

int h0(int);
int hash_function(int,int);

void insertElement(NODE*, int);

int main(void) {

    NODE table[MODULO];
    for(int i = 0; i<MODULO; i++) table[i].key = SENTINELA;

    insertElement(table, 19);
    insertElement(table, 36);
    insertElement(table, 5);
    insertElement(table, 21);
    insertElement(table, 4);
    insertElement(table, 26);
    insertElement(table, 14);

    for(int i  = 0; i<MODULO; i++) printf("%d ", table[i].key);

    return 0;
}

int h0(int key) {
    return key % MODULO;
}

int hash_function(int key,int index) {
    return (h0(key)+index) % MODULO;
}

void insertElement(NODE table[MODULO], int key) {
    int incercare = 0;
    int plasat = 0;

    while(plasat == 0 && incercare<MODULO) {
        int location = hash_function(key,incercare);
        if(table[location].key == SENTINELA) {
            table[location].key = key;
            printf("Elementul %d a fost plasat la adresa %p.\n", key, table[location]);
            plasat = 1;
        } else {
            incercare++;
        }
    }

    if(incercare >= MODULO) printf("Elementul nu se poate plasa.");
}
