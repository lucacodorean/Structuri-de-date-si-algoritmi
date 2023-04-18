/*
    coada cu vector circular.
    head, tail, actual_size, capacity.

*/

#include <stdlib.h>
#include <stdio.h>
#include "queue.h"

int main(void) {

    int capacity = 10;
    CIRCULAR_QUEUE* my_queue = init(capacity);

    for(int i = 0; i<8; i++) {
        enqueue(my_queue, i);
    }

    enqueue(my_queue, 9);
    enqueue(my_queue, 10);
    

    printf("Element extras din coada: %d\n", dequeue(my_queue));
    printf("Element extras din coada: %d\n", dequeue(my_queue));

    print(my_queue);

    dealloc(my_queue);
    return 0;
}