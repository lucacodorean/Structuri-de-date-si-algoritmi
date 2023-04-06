/**
 * @file tabela_dispersie.c
 * @author Luca-Andrei Codorean
 * @brief  Se cere implementarea functionalitatii unei tabele de dispersie, folosind metoda chaining.
 * @version 0.1
 * @date 2023-03-31
 * 
 * @copyright Copyright (c) 2023
**/


#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define A    3 
#define MOD 13
#define FILE_ERROR 400

typedef struct _node { 
    int first_key, second_key;
    struct _node* next;
} NODE;

NODE* create_node(int, int);

int hash(int,int);
void solve_first_task(NODE**,  int,     FILE*);
void solve_second_task(NODE**, int,     FILE*);
void display_table(NODE**,     int,     FILE*);

int main(void) {

    FILE* f_in  = fopen("input.in", "r");
    FILE* f_out = fopen("output.out", "w");

    if(f_in == NULL || f_out == NULL) {
        printf("ERROR: Eroare la operarea fisierelor I/O.");
        return FILE_ERROR;
    }

    int limit = -1;
    while(limit%2!=0) {
        printf("LIMIT_INIT: Se extrage un numar din fisier.");
        fscanf(f_in, "%d", &limit);
    }

    NODE** table = (NODE**)calloc(limit, sizeof(NODE*));
    for(int i = 0; i<limit; i++) {
        table[i] = (NODE*)calloc(1, sizeof(NODE));
    }

    solve_first_task(table,  limit, f_in);
    solve_second_task(table, limit, f_in);
    display_table(table, limit, f_out);

    fclose(f_in); f_in = NULL;
    fclose(f_out); f_out = NULL;

    printf("\nCompiled in: %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}



/// @brief Cream un nod
/// @param first_key - primul key a fiecarui element din lista
/// @param second_key - al doilea key pentru fiecare element din lista.
NODE* create_node(int first_key, int second_key) {
    NODE* new_node = (NODE*)calloc(1,sizeof(NODE));
    new_node->first_key     = first_key;
    new_node->second_key    = second_key;
    new_node->next          = NULL;
    return new_node;
}


/// functia de hasing doar ca facuta ca sa pot sa prelucrez datele. se paote modifica oricum, nu e relevanta pentru restul problemei.
int hash(int x, int y) { return ((x<<A) | y) % MOD; }

/// @brief  Prima cerinta a problemei.
/// @param table - locul in care vom prelucra datele
/// @param limit - marima tabelei
/// @param f     - parametru prin care transmitem fisierul de intrare.
void solve_first_task(NODE** table, int limit, FILE* f) {
    float alpha = 0;
    printf("TASK 1: Se preiau %d numere din fisier.", limit);
    for(int i = 0,x, y; i<limit/2; i++) {
        fscanf(f, "%d %d", &x, &y);

        int table_index = hash(x,y);

        if(table_index < limit) {                                       /// adaugam in tabela doar daca rezultatul functiei de hashing este mai mic decat limita impusa.
            NODE* new_node = create_node(x,y);                          /// urmeaza inserarea intr-o lista simplu inlantuita.

            if(table[table_index] == NULL) {
                table[table_index] = new_node;
            } else {
                new_node->next = table[table_index];
                table[table_index] = new_node;
            }

            alpha++;                                                   /// alpha creste pentru a determina factorul de umplere. f_umplere = alpha/limit.
        }
    }

    printf("\nFactorul de umplere este egal cu: %0.3f.", alpha/(1.0*limit));
}

/// @brief A doua cerinta a problemei: eliminarea unui element din tabela.
void solve_second_task(NODE** table, int limit, FILE* f) {
    int x, y;
    printf("\nTASK 2: Se preiau pentru corespunzatoare perechii de elemenete pe care doriti sa o stergeti, din fisierul de intrare.");
    fscanf(f, "%d %d", &x, &y);

    int table_index = hash(x,y);

    NODE* temp = table[table_index];                                                    /// se urmareste algoritmul de stergere dupa cheie.
    if(table[table_index]->first_key == x && table[table_index]->second_key == y) {
        table[table_index] = table[table_index]->next;
        if(table[table_index]==NULL) {
            free(table[table_index]);
        }
        return;
    }

    NODE* previous = NULL;
    while(temp!=NULL) {
        if(temp->first_key == x && temp->second_key == y) break;
        previous = temp;
        temp = temp->next;
    }

    previous->next = temp->next;
    free(temp);
    return;
}


///@brief
/*  Functie basic de display, pentru fiecare lista din table, cu indice de la 0 la limit, in fisierul f.
    Am folosit \t pentru tabulare, ca sa arate mai frumos fisierul.
    Tripleta (pointer, integer, integer) s-ar traduce: "la adresa pointer, se gaseste perechea integer, integer."
    Am transmis tabelul cu liste ca un pointer la pointer, deci am avea nevoie de un pointer de parcrugere pt fiecare linie, de aceea folosim pointerul temp. 
*/
void display_table(NODE** table, int limit, FILE* f) {
    for(int i = 0; i<limit; i++) {
        if(table[i]->next!=NULL) {
            fprintf(f,"\n%d\t| ", i);
            NODE* temp  = table[i];
            while(temp->next!=NULL) {
                fprintf(f,"     \t(%p (%d, %d)) ", temp, temp->first_key, temp->second_key);
                temp = temp->next;
            }
        }
    }
}
