#ifndef _QUEUE_H_
    #include <stdlib.h>
    #include <stdio.h>

    typedef struct _node { 
        int key;
        struct _node* next;
    } NODE;

    typedef struct _queue { 
        NODE* head; 
        NODE* tail;
    } QUEUE;

    int     empty(QUEUE*);
    int     dequeue(QUEUE*);
    NODE*   create_node_q(int);
    void    enqueue(QUEUE*, int);
    void    dealloc_queue(QUEUE*);
    void    print_queue(QUEUE*, FILE*);
#endif