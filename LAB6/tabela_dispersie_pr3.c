#include <stdio.h>
#include <stdlib.h>

#define MODULO 7
#define C1     1
#define C2     1
#define SENTINELA -9999999

typedef struct {
    int key;
} NODE;

int h_prim(int);
int hash_function(int, int);

void insertElement(NODE*, int);
void findElement(NODE*, int);

int main(void) {

    NODE table[MODULO];
    for(int i = 0; i<MODULO; i++) table[i].key = SENTINELA;

    insertElement(table, 19);
    insertElement(table, 36);
    insertElement(table,  5);
    insertElement(table, 21);
    insertElement(table,  4);
    insertElement(table, 26);
    insertElement(table, 14);

    printf("Elementele din lista:\n\t");
    for(int i = 0; i<MODULO; i++) printf("%d ", table[i].key);

    return 0;

}

int h_prim(int key) {
    return key % MODULO;
}

int hash_function(int key, int incercare) {
    return (h_prim(key) + C1 * incercare + C2 * (incercare * incercare));
}

void insertElement(NODE* table, int key) {
    int incercare = 0;
    int plasat = 0;

    while(plasat == 0 && incercare < MODULO) {
        int location = hash_function(key, incercare);
        if(location >= MODULO) {
            printf("Elementul %d nu poate fi adaugat.\n", key);
            break;
        }

        if(table[location].key == SENTINELA) {
            table[location].key = key;
            printf("Elementul %d a fost plasat la adresa %p.\n", key, &table[location].key);
            plasat = 1;
        } else {
            incercare++;
        }
    }
}

void findElement(NODE* table, int key) {
    int ok = 0;
    for(int i = 0; i<MODULO; i++) {
        if(table[i].key == key) {
            ok = 1;
            printf("Elementul a fost gasit la adresa: %p.\n", &table[i].key);
            break;
        }
    }

    if(ok = 0) printf("Elementul nu a fost gasit.");
}
