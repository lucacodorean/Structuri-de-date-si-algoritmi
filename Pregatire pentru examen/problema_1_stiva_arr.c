#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int size, cap, top;
    int* arr;
} STIVA;

void    pop(STIVA*);
int     empty(STIVA*);
void    push(STIVA*, int);
STIVA*  init_stiva(int);
void    free_stack(STIVA*); 


int main() {
    STIVA* my_stack = init_stiva(5);

    push(my_stack, 1);
    push(my_stack, 2);
    push(my_stack, 3);
    pop(my_stack);
    push(my_stack, 4);
    push(my_stack, 5);
    push(my_stack, 6);
    push(my_stack, 7);

    for(int i = 0; i<6; i++) {
        pop(my_stack);
    }

    free_stack(my_stack);

    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

STIVA* init_stiva(int maximum_capacity) {
    STIVA* stiva = (STIVA*)calloc(1,sizeof(STIVA));
    stiva->cap = maximum_capacity;
    stiva->size = 0;
    stiva->top = 0;
    stiva->arr = (int*)calloc(stiva->cap, sizeof(int));
    return stiva;
}

int empty(STIVA* stiva) {
    return stiva->size == 0;
}

void push(STIVA* stiva, int value) {
    if(stiva->size == stiva->cap) {
        printf("\nError: Maximum capacity reached. \n\tImpossible to insert element: %d.", value);   
        return;
    }
    
    stiva->top = value;
    stiva->arr[++(stiva->size)] = value;
    printf("\nInfo: Element %d has been added to the stack. \n\tCurrent size: %d | Top: %d", value, stiva->size, stiva->top);
    return;
}

void pop(STIVA* stiva) {
    if(empty(stiva)) {
        printf("\nError: Stack is empty.");
        return;
    }

    int aux = stiva->arr[stiva->size];
    stiva->top = stiva->arr[--(stiva->size)];
    printf("\nElement %d has been eliminated from the stack. \n\tCurrent size: %d | Top: %d", aux, stiva->size, stiva->top);
    return;
}

void free_stack(STIVA* stiva) {
    free(stiva->arr); stiva->arr = NULL;
    stiva->size = 0;
    stiva->top  = 0;
    stiva->cap  = 0;
    return;
}