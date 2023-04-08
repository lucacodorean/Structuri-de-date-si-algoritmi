#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 404
#define SENTINELA  '-'

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} NODE;

NODE* create_node(int);
NODE* create_tree(FILE*);
void  schimba_sub_arbori(NODE*);
void  parcurge_inordine(NODE*, FILE*);
void  deallocate_tree(NODE*);

int main(void) {

    FILE* f_in  = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    NODE* tree = create_tree(f_in);  fclose(f_in);
    parcurge_inordine(tree, f_out);  

    schimba_sub_arbori(tree);

    fprintf(f_out, "\n");
    parcurge_inordine(tree, f_out);  fclose(f_out);

    deallocate_tree(tree);
    
    return 0;

}

NODE* create_node(int key) {
    NODE* new_node = (NODE*)calloc(1,sizeof(NODE));
    new_node->key = key;
    new_node->left = new_node->right = NULL;
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

void schimba_sub_arbori(NODE* tree) {
    NODE* temp = NULL;
    temp = tree ->right;
    tree->right = tree->left;
    tree->left  = temp;
}

void parcurge_inordine(NODE* tree, FILE* path) {
    if(tree == NULL) return;

    parcurge_inordine(tree->left, path);
    fprintf(path, "%d ", tree->key);
    parcurge_inordine(tree->right, path);
}

void deallocate_tree(NODE* tree) {
    if(tree==NULL) return;

    deallocate_tree(tree->left);  tree->left  = NULL;
    deallocate_tree(tree->right); tree->right = NULL;
    free(tree); tree = NULL;
}