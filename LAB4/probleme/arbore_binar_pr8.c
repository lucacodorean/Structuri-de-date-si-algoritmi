#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_ERROR 404
#define SENTINELA  ' '
#define NODES_MAX  512

typedef struct _node {
    char key;
    struct _node* left;
    struct _node* right;
    struct _node* next;
} NODE;


NODE* stack = NULL;
NODE* create_node(char);
NODE* create_tree(char*);
void  deallocate_tree(NODE*);
void  parcurgere(NODE*, FILE*);

NODE* pop();
void  push(NODE*);

char* operators = "+-\\%%*";

int main(void) {

    FILE* f_in  = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    char* buffer = (char*)calloc(NODES_MAX, sizeof(char));
    fscanf(f_in, "%[^\n]", buffer); fclose(f_in);

    NODE* stack = NULL;
    NODE* tree = create_tree(buffer);
    
    free(buffer); buffer = NULL;

    parcurgere(tree, f_out);

    return 0;
}

void  parcurgere(NODE* tree, FILE* path) {
    if(tree == NULL) return;
    
    parcurgere(tree->left, path);
    fprintf(path, "%c", tree->key);
    parcurgere(tree->right, path);
}

NODE* create_node(char key) {
    NODE* new_node = (NODE*)calloc(1,sizeof(NODE));
    new_node->key = key;
    new_node->left = new_node->right = new_node->next = NULL;
    return new_node;
}

void push(NODE* new_node) {
    if(stack == NULL) {
        stack = new_node;
    } else {
        new_node->next = stack;
        stack = new_node;
    }
}

NODE* pop() {
    if(stack!=NULL) {
        NODE* temp = stack;
        stack = stack->next;
        return temp;
    }
}

NODE* create_tree(char* buffer) {
    if(strlen(buffer) == 0) return NULL;
    
    NODE* tree         = NULL;
    NODE* left_child   = NULL;
    NODE* right_child  = NULL;

    for(int i = 0; i<strlen(buffer); i++) {
        if(buffer[i] == SENTINELA) continue;
        if(strchr(operators,buffer[i])) {
            tree = create_node(buffer[i]);
            right_child = pop();
            left_child = pop();
            
            tree->left = left_child;
            tree->right = right_child;
            push(tree);
           
        } else {
            tree = create_node(buffer[i]);
            push(tree);
        }
    }
    return tree;
}
