#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 404

typedef struct _node {
    int key;
    struct _node* next;
} LIST;


LIST* createNode(int);
void  print_list(FILE*, LIST*);
void  insert_element(LIST**, int);
int   find_element(LIST*, int);

int main(void) {

    FILE* f_in  = fopen("date.txt", "r");
    FILE* f_out = fopen("date.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului.");
        return FILE_ERROR;
    }

    int size; fscanf(f_in, "%d", &size);
    LIST* list = NULL;

    for(int i = 0, number; i<size; i++) {
        fscanf(f_in, "%d ", &number);
        insert_element(&list, number);
    } fclose(f_in);

    print_list(f_out, list); 
    fclose(f_out);

    free(list); list = NULL;

    return 0;
}

LIST* createNode(int key) {
    LIST* new_node = (LIST*)calloc(1,sizeof(LIST));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void print_list(FILE* f, LIST* list) { 
    LIST* temp = list;
    while(temp != NULL) {
        fprintf(f,"%d ", temp->key);
        temp = temp->next;
    }
}

int find_element(LIST* list, int key) {
    LIST* temp = list;
    while(temp != NULL) {
        if(temp->key == key) return 1;
        temp = temp->next;
    }

    return 0;
}

void insert_element(LIST** list, int key) {

    LIST* new_node = createNode(key);
    if(*list == NULL)  {
        *list = createNode(key);
    } else { 
        LIST* temp = *list;
        if(find_element(temp, key) == 1) return;

        while(temp->next != NULL) {
            temp = temp ->next;
        }

        temp -> next = new_node;
    }
}