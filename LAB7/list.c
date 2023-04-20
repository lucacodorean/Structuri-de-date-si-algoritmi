#include <stdlib.h>
#include <stdio.h>
#include "list.h"

NODET* create_node(int key) {
    NODET* new_node = (NODET*)calloc(1,sizeof(NODET));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void dealloc_list(NODET* list) {
    if(list == NULL) return;

    NODET* temp = NULL;
    while(list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}

void add_to_list(NODET** list, int key) {
    if(*list == NULL) {
        *list = create_node(key);
    } 

    NODET* temp = *list;
    NODET* new_node = create_node(key);

    new_node->next = temp;
    *list = new_node;
}

void print_list(FILE* path, NODET* list) {
    if(list == NULL) return;
    
    NODET* temp = list;
    while(temp != NULL) {
        fprintf(path, "%d ", temp->key);
        temp = temp->next;
    }
}

int search(NODET* list, int key) {
    if(list == NULL) return 0;

    NODET* temp = list;
    while(temp != NULL) {
        if(temp->key == key) return 1;
        temp = temp->next;
    }

    return 0;
}