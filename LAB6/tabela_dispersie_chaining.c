#include <stdlib.h>
#include <stdio.h>

#define MODULO 8

typedef struct _node {
    int key;
    struct _node* next;
} NODE;

NODE* create_node(int);
int hash_function(int);

void print_list(NODE*);

void insertElement(NODE**, int);
NODE* findElement(NODE**,  int);
void deleteElement(NODE**, int);
void print_table(NODE**);

int main(void) {

    NODE* table[MODULO];

    for(int i = 0; i<MODULO; i++) table[i] = NULL;

    insertElement(table,19);
    insertElement(table,36);
    insertElement(table,5);
    insertElement(table,21);
    insertElement(table,4);
    insertElement(table,26);
    insertElement(table,14);

    print_table(table);

    NODE* gasit = findElement(table,4);
    if(gasit!=NULL) {
            printf("\nElementul %d gasit la adresa %p.\n", gasit->key, gasit);
    } else printf("\nElementul nu a fost gasit.\n");

    deleteElement(table, 4);
    deleteElement(table, 21);
    deleteElement(table, 5);

    print_table(table);
    return 0;
}

NODE* create_node(int key) {
    NODE* new_node = (NODE*)calloc(1,sizeof(NODE));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

int hash_function(int key) {
    return key % MODULO;
}

void insertFirst(NODE** list, int key) {
    NODE* new_node = create_node(key);
    if(*list == NULL) {
        *list = new_node;
    } else {
         new_node -> next = *list;
        *list = new_node;
    }

}
void insertElement(NODE** table, int key) {
    int location = hash_function(key);
    insertFirst(&table[location], key);
}

NODE*  findElement(NODE** table,  int key) {
    int location = hash_function(key);
    NODE* aux = table[location];

    while(aux != NULL) {
        if(aux->key == key) return aux;
        aux = aux->next;
    }

    return NULL;
}

void deleteElement(NODE** table, int key) {
    int location = hash_function(key);

    NODE* current = table[location];
    NODE* previous = NULL;

    while(current!=NULL) {
        if(current->key == key) break;
        previous = current;
        current = current->next;
    }

    if(current != NULL)  {
        if(current == table[location]) {
                table[location] = current->next;
        }
        else {
            previous -> next = current ->next;
        }
        free(current);
    }
}

void print_list(NODE* list) {
    NODE* aux = list;
    while(aux!=NULL) {
        printf("(%p | %d) ", aux, aux->key);
        aux = aux->next;
    }
}

void print_table(NODE** table) {
    for(int i = 0; i<MODULO; i++) {
            printf("\ni: %d| ", i);
            print_list(table[i]);
    }
}
