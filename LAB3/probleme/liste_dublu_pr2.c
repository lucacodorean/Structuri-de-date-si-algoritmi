#include <stdlib.h>
#include <stdio.h>

typedef struct _node {
    int key;
    struct _node* next;
} STACK;

STACK* create_node(int);
void push(STACK**, int);
void pop(STACK*, int*);
void print(STACK*);

int main(void) {
    STACK* my_stack = NULL;
    push(&my_stack, 5);
    push(&my_stack, 4);
    push(&my_stack, 3);

    print(my_stack);

    int element = 0;
    pop(my_stack, &element);


    printf("%d", element);

    return 0;
}

STACK* create_node(int key) {
    STACK* new_node = (STACK*)calloc(1,sizeof(STACK));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void push(STACK** stack, int key){ 
    STACK* new_node = create_node(key);
    if(*stack == NULL) {
        *stack = new_node;
    } else {
        new_node->next = *stack;
        *stack = new_node;
    }
}

void print(STACK* my_stack) {
    STACK* temp = my_stack;
    while(temp!=NULL) {
        printf("%p %d\n", temp, temp->key);
        temp = temp ->next;
    }
}

void pop(STACK* stack, int* element) {
    if(stack == NULL) return;

    *element = stack->key;
    stack = stack->next;
}