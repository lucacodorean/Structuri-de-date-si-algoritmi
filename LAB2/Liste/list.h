#ifndef _C_LIST_
    #define _C_LIST_

    typedef struct node {
        int key;
        struct node* next;
    } NodeT;


    NodeT* create(int);
    void print_list(NodeT*);
    NodeT* search(NodeT*, int);
    void reverse(NodeT**);

    void insert_last(NodeT**, NodeT**, int);
    void insert_first(NodeT**, NodeT**, int);
    void insert_after_key(NodeT**, NodeT**, int, int);
    
    void delete_first(NodeT**, NodeT**);
    void delete_last(NodeT**, NodeT**);         /// tbd
    void delete_key(NodeT**, NodeT**, int);    /// tbd
#endif // _C_LIST_