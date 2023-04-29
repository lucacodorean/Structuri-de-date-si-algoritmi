#ifndef __STACK__H
    #define NO_ELEMENT_FOUND 404

    typedef struct node {
        int key;
        struct node* next;
    } NodeT;

    #define STACK NodeT

    int  pop(NodeT**);
    NodeT* create_node(int);
    void push(NodeT**, int);
    void print_stack(NodeT*);
    int empty(NodeT**);
#endif