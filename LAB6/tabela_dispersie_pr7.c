#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _node {
    char* key;
    struct _node* next;
} TABLE;

#define MODULO 7

TABLE* create_node(char*);
void  init_table(TABLE**);
void  print_list(TABLE*);
void  print_table(TABLE**);
void  insertElement(TABLE**, char*);

int hash_code(char*);
int hash_function(int);

int main(void) {

    TABLE** table = (TABLE**)calloc(MODULO,sizeof(TABLE*));
    init_table(table);

    insertElement(table,"mar");
    insertElement(table,"var");
    insertElement(table,"lup");
    insertElement(table,"mop");
    insertElement(table,"dop");
    insertElement(table,"urs");
    insertElement(table,"cuc");
    insertElement(table,"laborator");
    insertElement(table,"date");
    insertElement(table,"structura");

    print_table(table);

    
    for(int i = 0; i<MODULO; i++) {
        free(table[i]); table[i] = NULL;
    }
    free(table); table = NULL;

    printf("Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}


int hash_code (char* key) {
    int sum = 0;
    for(int i = 0; i<strlen(key); i++) {
        sum+=(int)key[i];
    }
    return (sum % strlen(key));
}

int hash_function(int value) {
    return value % MODULO;
}

TABLE* create_node(char* key) {
    TABLE* new_node = (TABLE*)calloc(1,sizeof(TABLE));
    new_node->key = key;
    new_node->next = NULL;
}

void init_table(TABLE** table) {
    for(int i = 0; i<MODULO; i++) {
        table[i] = (TABLE*)calloc(1,sizeof(TABLE));
    }
}

void insertElement(TABLE** table, char* key) {
    
    int location = hash_function(hash_code(key));
    TABLE* new_node = create_node(key);

    if(table[location] == NULL) {
        table[location] = new_node;
    } else {
        new_node->next = table[location];
        table[location] = new_node;
    }
}

void print_list(TABLE* list) {
    TABLE* temp = list;
    while(temp->next!= NULL) {
        printf("(%p | %s) ", temp, temp->key);
        temp = temp->next;
    }
    printf("\n");
}

void print_table(TABLE** table) {
    for(int i = 0; i<MODULO; i++) {

       
        if(table[i] != NULL) { 
            printf(" %d: ", i);
            print_list(table[i]);
        }
        else printf("Tabela nula.\n");
    }
} 