#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

NodeT* create_node(int given_key) {
    NodeT* new_node = (NodeT*)calloc(1,sizeof(NodeT));

    new_node->key = given_key;
    new_node->next = NULL;
    return new_node;
}

void push(NodeT** stack, int key) {
    NodeT* new_node = create_node(key);
    if(*stack==NULL) {
        *stack = new_node;
    } else {
        new_node->next = *stack;
        *stack = new_node;
    }
}

int pop(NodeT** stack) {
    if(*stack == NULL) {
        printf("Nu exista elemente in stiva.");
        return NO_ELEMENT_FOUND;
    } else {

        NodeT* copy = *stack;
        int value = (*stack)->key;
        *stack = (*stack)->next;
        free(copy);

        return value;
    }
}

void print_stack(NodeT* stack) {
    while(stack!=NULL) {
        printf("\t%d, %p\n", stack->key, stack);
        stack = stack->next;
    }
}