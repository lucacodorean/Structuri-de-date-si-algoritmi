/*
    Stiva implementata cu lista simplu inlantuita.
        Avem nevoie de operatia de push si pop.
            push -> insert_first();
            pop  -> delete_first(); -> returneaza int;
*/

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main(void) {
    NodeT* stack = NULL;

    for(int i = 0; i<11; i++) push(&stack, i);
    printf("Elementul din varful stivei este: %d.\n", pop(&stack));
    

    printf("Dupa pop, in stiva se gasesc:\n");
    print_stack(stack);

    return 0;
}

