#ifndef __QUEUE__H
    #define NOT_ELEMENT_FOUND   404

    typedef struct {
        int capacity, size;
        int head;
        int tail;
        int* elements;
    } CIRCULAR_QUEUE;

    CIRCULAR_QUEUE* init(int);         /// initializeaza o coada circulara cu o anume capacitate;
    void print(CIRCULAR_QUEUE*);
    int dequeue(CIRCULAR_QUEUE*);
    void enqueue(CIRCULAR_QUEUE*, int);
    void dealloc(CIRCULAR_QUEUE*);
#endif