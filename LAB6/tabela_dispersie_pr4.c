#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef _HASH_TABLE__
    typedef struct _node {
        int key;
    } LIST;

    #include <limits.h>
    #define SENTINELA INT_MIN
    #define MODULO          7
    
    LIST* searchElement(LIST*, int);
    void  insertElement(LIST*, int);
    void  init_table(LIST*);
    void  print_list(LIST*);

    int first_hash_function(int);
    int second_hash_function(int);
    int hash_function(int, int);
#endif

int main(void) {

    LIST tabela_dispersie[MODULO];
    init_table(tabela_dispersie);

    insertElement(tabela_dispersie, 19);
    insertElement(tabela_dispersie, 36);
    insertElement(tabela_dispersie,  5);
    insertElement(tabela_dispersie, 21);
    insertElement(tabela_dispersie,  4);
    insertElement(tabela_dispersie, 26);
    insertElement(tabela_dispersie, 14);

  
    LIST* cautat_1 = searchElement(tabela_dispersie, 4);
    LIST* cautat_2 = searchElement(tabela_dispersie, 7);

    if(cautat_1 != NULL) printf("\nElementul %d a fost gasit la adresa %p.\n", cautat_1->key, cautat_1);
    else printf("Elementul nu a fost gasit.\n");

    if(cautat_2 != NULL) printf("Elementul %d a fost gasit la adresa %p.\n", cautat_2->key, cautat_2);
    else printf("Elementul nu a fost gasit.\n");

    print_list(tabela_dispersie);
    printf("\nCompiled in %0.3f seconds.", clock()*1.0/ CLOCKS_PER_SEC);
    return 0;
}

int first_hash_function(int key) {
    return key % MODULO;
}

int second_hash_function(int key) {
    return 5 - (key % 5);
}

int hash_function(int key, int index) {
    return (first_hash_function(key) + (index * second_hash_function(key))) % MODULO;
}


void init_table(LIST* list) {
    for(int i = 0; i<MODULO; i++) list[i].key = SENTINELA;
}

void insertElement(LIST* list, int key) {
    int incercari = 0;
    int plasat = 0;
    
    while(plasat == 0 && incercari < MODULO) {
        int location = hash_function(key, incercari);
        if(location >= MODULO) {
            printf("Elementul %d este imposibil de adaugat in tabela.\n", key);
            return;
        } else {
            if(list[location].key != SENTINELA) {
                incercari++;
            } else {
                plasat = 1;
                list[location].key = key;
                printf("Elementul %d a fost plasat la adresa %p.\n", key, &list[location]);
            }
        }
    }
}

LIST* searchElement(LIST* list, int key) {
    int ok = 0;
    for(int i = 0; i<MODULO && ok == 0; i++) {
        if(list[i].key == key) {
            ok = 1;
            return &list[i];
        }
    }

    return NULL;
}

void print_list(LIST* list) {
    for(int i = 0; i<MODULO; i++) printf("(%p | %d) ", &list[i], list[i].key);
}