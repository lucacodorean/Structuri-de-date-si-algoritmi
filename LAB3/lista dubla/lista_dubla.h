#ifndef _LISTA_DUBLA_H_
    typedef struct node {
        int key;
        struct node* next;
        struct node* previous;
    } NodeDL;

    typedef struct {
        NodeDL* head;
        NodeDL* tail;
    } DOUBLE_LINKED_LIST;

    NodeDL* create_node(int);
    void insert_last(DOUBLE_LINKED_LIST*, int);
    void display_reverse(DOUBLE_LINKED_LIST);        /// ex. de parcurgere in sens invers;

#endif