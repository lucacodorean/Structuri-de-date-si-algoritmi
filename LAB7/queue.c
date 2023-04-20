#include "queue.h"

NODE* create_node_q(int key) {
    NODE* new_node = calloc(1,sizeof(NODE));
    new_node->key = key;
    new_node->next = NULL;
    return new_node;
}

void enqueue(QUEUE* queue, int key) {
   NODE* new_node = create_node_q(key);
   if(queue->head == NULL) {
        queue->head = new_node;
        queue->tail = new_node;
   } else {
        queue->tail->next = new_node;
        queue->tail = new_node;
   }
}

int dequeue(QUEUE* queue) {
    if(queue->head == NULL) return -1;

    NODE* temp = queue->head;
    queue->head = queue->head->next;

    if(queue->head == NULL) queue->tail = NULL;

    int result = temp->key;
    return result;
}

void dealloc_queue(QUEUE* queue) {
    NODE* temp = queue->head;
    while(queue->head != NULL) {
        temp = queue->head;
        queue->head = queue->head->next;
        free(temp);
    }
}

void print_queue(QUEUE* queue, FILE* path) {
    if(queue->head == NULL) return;

    NODE* temp = queue->head;
    while(temp != NULL) {
        fprintf(path, "%d ", temp->key);
        temp = temp->next;
    }
}

int empty(QUEUE* queue) {
    return (queue->head == NULL);
}