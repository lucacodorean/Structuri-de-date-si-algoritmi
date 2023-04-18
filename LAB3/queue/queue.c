#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

CIRCULAR_QUEUE* init(int capacity) {
    CIRCULAR_QUEUE* new_queue = (CIRCULAR_QUEUE*)calloc(1,sizeof(CIRCULAR_QUEUE));
    new_queue->capacity = capacity;
    new_queue->elements = (int*)calloc(new_queue->capacity, sizeof(int));
    new_queue->size = new_queue->head = new_queue->tail = 0; 
    return new_queue;
}

void enqueue(CIRCULAR_QUEUE* queue, int value) {
    if(queue->size+1 > queue->capacity) {
        printf("Coada este deja plina.");
        return;
    }

    queue->elements[queue->tail] = value;
    queue->size++;
    if(queue->tail == queue->capacity) {
        queue->tail = 1;
    } else {
        queue->tail++;
    }
}

int dequeue(CIRCULAR_QUEUE* queue) {
    if(queue->size == 0) {
        printf("Nu exista elemente in coada.");
        return NOT_ELEMENT_FOUND;
    }

    int value = queue->elements[queue->head];
    if(queue->capacity == queue->head) {
        queue->head = 1;
    } else {
        queue->head++;
    }
    return value;
}

void print(CIRCULAR_QUEUE* queue) {
    if(queue->head > queue->tail) {
        int aux = queue->head; 
        queue->head = queue->tail;
        queue->tail = aux;
    }

    for(int i = queue->head; i!=queue->tail; i++) printf("%d\n", queue->elements[i]);
}

void dealloc(CIRCULAR_QUEUE* queue) {
    for(int i = queue->head; i!=queue->tail; i++) free(&(queue->elements[i]));
    free(queue); queue = NULL;
}