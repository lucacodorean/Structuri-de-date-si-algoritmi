#ifndef _LIST_H_
    #include <stdio.h>
    #include <stdlib.h>

    typedef struct node {
        int key;
        struct node* next;
    } NODET;

    NODET* create_node(int);
    void  dealloc_list(NODET*);
    void  add_to_list(NODET**, int);
    void  print_list(FILE*, NODET*);
    int   search(NODET*, int);
#endif