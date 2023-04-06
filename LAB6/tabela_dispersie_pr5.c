#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define FILE_ERROR 404
#define TEXT_LIMIT 256

typedef struct _node {
    char* key;
    struct _node* next;
} TABLE;

TABLE*  create_Node(char*);
void    print_list(TABLE*);
void    init_table(TABLE**, int);
void    print_table(TABLE**, int);
void    deallocate_table(TABLE**, int);
int     find_Element(TABLE**, char*, int);
void    insert_Element(TABLE**, char*, int);

int     hash_function(char*, int);

int main(void) {

    FILE*  f_in = fopen("date.txt", "r");
    FILE* f_out = fopen("date.out", "w");

    char* string  = (char*)calloc(TEXT_LIMIT, sizeof(char));
    char** buffer = (char**)calloc(TEXT_LIMIT,sizeof(char*));

    for(int i = 0; i<TEXT_LIMIT; i++) {
        buffer[i] = (char*)calloc(TEXT_LIMIT,sizeof(char));
    }
    
    if(f_in == NULL || f_out == NULL) {
        fprintf(f_out, "Eroare la prelucrarea fisierelor.");
        return FILE_ERROR;
    }

    fscanf(f_in, "%s", string);
    int table_size = 0;
    while(fscanf(f_in, "%s", buffer[table_size]) != EOF) {
        table_size++;
    } fclose(f_in); f_in = NULL;

    int sequence_size = strlen(buffer[0]);

    TABLE** table = (TABLE**)calloc(table_size,sizeof(TABLE*));
    init_table(table, table_size);

    for(int i = 0; i<table_size; i++) {
        insert_Element(table, buffer[i], table_size);
        free(buffer[i]); buffer[i] = NULL;
    } free(buffer); buffer = NULL;


    int solution = 0;
    for(int i = 0; i<strlen(string); i++) {
        char* to_be_evaluated = (char*)calloc(sequence_size,sizeof(char));
        int l = 0;
        if(i > strlen(string) - sequence_size) break;


        for(int j = i; j<i+sequence_size; j++) to_be_evaluated[l++] = string[j];
        solution += find_Element(table, to_be_evaluated, table_size);

        free(to_be_evaluated); to_be_evaluated = NULL;
    }
    
    fprintf(f_out, "%d", solution);

    free(string); string = NULL;
    deallocate_table(table, table_size);

    fprintf(f_out, "\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    fclose(f_out); f_out = NULL;
    
    return 0;
}

int hash_function(char* key, int table_size) {
    int sum = 0;
    for(int i = 0; i<strlen(key); i++) {
        sum += key[i];
    }

    return (int)(sum / strlen(key)) % table_size; 
}

TABLE* create_Node(char* key) {
    TABLE* new_node = (TABLE*)calloc(1,sizeof(TABLE));
    new_node->key = (char*)calloc(TEXT_LIMIT, sizeof(char));
    strcpy(new_node->key, key);
    new_node->next = NULL;
    return new_node;
}

void insert_Element(TABLE** table, char* key, int table_size) {
    int location = hash_function(key, table_size);

    TABLE* new_node = create_Node(key);

    if(table[location] == NULL) {
        table[location] = new_node;
    } else {
        new_node->next = table[location];
        table[location] = new_node;
    }
}

void print_list(TABLE* parameter) {
    TABLE* temp = parameter; 
    while(temp != NULL) {
        printf("(%p | %s) ", temp, temp->key);
        temp = temp->next;
    }
    printf("\n");
} 

void print_table(TABLE** table, int limit) {
    for(int i = 0; i<limit; i++) {
        printf("%d | ", i);
        print_list(table[i]);
    }
}

void init_table(TABLE** table, int table_size) {
    for(int i = 0; i<table_size; i++) {
        table[i] = (TABLE*)calloc(1, sizeof(TABLE));
    }
}

int find_Element(TABLE** table, char* key, int table_size) {
    int location = hash_function(key, table_size);
    TABLE* temp = table[location];

    while(temp->next != NULL) {
        if(strcmp(temp->key, key)==0) return 1;
        temp = temp->next;
    }
    return 0;
}

void deallocate_table(TABLE** table, int table_size) {
    for(int i = 0; i<table_size; i++) {
        free(table[i]); table[i] = NULL;
    }

    free(table); table = NULL;
}