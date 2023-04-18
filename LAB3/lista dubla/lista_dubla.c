#include <stdlib.h>
#include <stdio.h>
#include "lista_dubla.h"

NodeDL* create_node(int value) {
    NodeDL* new_node = (NodeDL*)calloc(1,sizeof(NodeDL));
    new_node->key = value;
    new_node->next = new_node->previous = NULL;
    return new_node;
}

void insert_last(DOUBLE_LINKED_LIST* list, int value) {

    NodeDL* new_node = create_node(value);

    if(list->head == NULL) {
        list->head = list->tail = new_node;
    } else {
        new_node->previous = list->tail;
        list->tail->next = new_node;
    }

    list->tail = new_node;
}

 void display_reverse(DOUBLE_LINKED_LIST list) {
    for(NodeDL* aux = list.tail; aux!=NULL;) {
        printf("%d\n", aux->key);
        aux = aux->previous;
    }
 }