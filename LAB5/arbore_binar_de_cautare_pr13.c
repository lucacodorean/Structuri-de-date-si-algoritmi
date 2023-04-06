#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_ERROR  404

typedef struct _node {
    float key;
    struct _node* left;
    struct _node* right;
} TREE;

TREE* create_node(float);
TREE* create_tree(TREE*, float);
void  parcurgere_inordine(TREE*,  FILE*);
void  deallocate_tree(TREE*);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    int size; fscanf(f_in, "%d", &size);

    TREE* original_tree = NULL;
    TREE* integers_tree = NULL;
    TREE* decimals_tree = NULL;

    float* original = (float*)calloc(size, sizeof(float));
    int*   integers = (int*)calloc(size, sizeof(int));
    float* decimals = (float*)calloc(size, sizeof(float));

    for(int i = 0; i<size; i++) {
        fscanf(f_in, "%f", &original[i]);
        integers[i] = (int)original[i];
        decimals[i] = (original[i] - (int)original[i]);
        original_tree = create_tree(original_tree, original[i]);
        integers_tree = create_tree(integers_tree, integers[i]);
        decimals_tree = create_tree(decimals_tree, decimals[i]);
    }
    
    fprintf(f_out, "Parcurgerea arborelui original: ");
    parcurgere_inordine(original_tree, f_out);
    fprintf(f_out, "\nParcurgerea arborelui de intregi: ");
    parcurgere_inordine(integers_tree, f_out);
    fprintf(f_out, "\nParcurgerea arborelui de numere zecimale: ");
    parcurgere_inordine(decimals_tree, f_out);


    free(decimals); free(integers); free(original);
    decimals = integers = original = NULL;

    deallocate_tree(original_tree);
    deallocate_tree(integers_tree);
    deallocate_tree(decimals_tree);

    printf("Compiled in %0.3f seconds.", clock()*1.0 / CLOCKS_PER_SEC);
    return 0;
}

TREE* create_node(float key) {
    TREE* new_node = (TREE*)calloc(1,sizeof(float));
    new_node->key = key;
    new_node->left = new_node ->right = NULL;
    return new_node;
}

TREE* create_tree(TREE* root, float key) {
    if(root == NULL) return create_node(key);
    else {
        if(key < root->key) root->left  = create_tree(root->left, key);
        if(key > root->key) root->right = create_tree(root->right, key);

        return root;
    }
}

void parcurgere_inordine(TREE* tree, FILE* path) {
    if(tree == NULL) return;
    
    parcurgere_inordine(tree->left, path);
    fprintf(path, "%0.2f ", tree->key);
    parcurgere_inordine(tree->right, path);

}

void  deallocate_tree(TREE* tree) {
    if(tree == NULL) return;

    free(tree->left);   tree->left  = NULL;
    free(tree->right);  tree->right = NULL;
    free(tree);         tree        = NULL;
}