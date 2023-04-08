#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 404
#define SENTINELA  '-'


typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} NODE;

int   max(int, int);
NODE* create_node(int);
NODE* create_tree(FILE*);
int  get_depth(NODE*, int);
void  deallocate_tree(NODE*);
void  parcurgere_inodrine(NODE*);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare");
        return FILE_ERROR;
    }

    NODE* tree = create_tree(f_in); 
    fclose(f_in); f_in = NULL;

    int min_depth = 0;
    int max_depth = get_depth(tree, min_depth);

    fprintf(f_out, "Adancimea maxima este %d.\n", max_depth);
    fprintf(f_out, "Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);

    fclose(f_out); f_out = NULL;

    deallocate_tree(tree);

    return 0;
}

NODE* create_node(int key) {
    NODE* new_node = (NODE*)calloc(1,sizeof(NODE));
    new_node->key = key;
    new_node->right = new_node->left = NULL;
    return new_node;
}

NODE* create_tree(FILE* path) {
    char buffer[100];
    fscanf(path, "%s", buffer);
    if(buffer[0] == SENTINELA) return NULL;
    
    int number; sscanf(buffer, "%d", &number);
    
    NODE* new_node  = create_node(number);
    new_node->left  = create_tree(path);
    new_node->right = create_tree(path);
    return new_node;
}

int max(int first, int second) {
    return first > second ? first : second;
}

int get_depth(NODE* root, int prev_depth) {
    if(root == NULL) return -1;

    prev_depth++;
    int ldepth = get_depth(root->left, prev_depth);
    int rdepth = get_depth(root->right, prev_depth);

    return max(ldepth, rdepth) + 1;
}


void parcurgere_inodrine(NODE* tree) {
    if(tree == NULL) return;
    printf("%d ", tree->key);
    parcurgere_inodrine(tree->left);
    parcurgere_inodrine(tree->right);
}

void deallocate_tree(NODE* tree) {
    if(tree == NULL) return;
    
    deallocate_tree(tree->left);    tree->left  = NULL;
    deallocate_tree(tree->right);   tree->right = NULL;
    free(tree);                     tree        = NULL;
}