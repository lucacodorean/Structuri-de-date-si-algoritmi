#ifndef __ARBORE_H__

    #include <stdio.h>
    #include <stdlib.h>

    #define SENTINELA           '-'
    #define max(a,b)            (((a) > (b)) ? (a) : (b))
    #define ELEMENT_NOT_FOUND   404

    typedef struct node {
        int key;
        struct node *left, *right;
    } NodeT;

    NodeT* createNode(int);
    NodeT* read_from_file(FILE*);

    void in_order(NodeT*);
    void pre_order(NodeT*);
    void post_order(NodeT*);

    int leaf_node(NodeT*);
    int internal_nodes(NodeT*);
    int get_height(NodeT*);
    void get_depth(NodeT*, int);

    NodeT* search(NodeT* , int);
#endif