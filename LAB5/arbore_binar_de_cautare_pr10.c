#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_ERROR   404
#define INVALID_DATA 405
#define SENTINELA     '-'
typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} TREE;


int     get_height(TREE*);
TREE*   create_node(int key);
int*    get_array(TREE*, int);
void    deallocate_tree(TREE*);
TREE*   create_tree(TREE*, int);
void    display_inorder(TREE*, FILE*);
void    parcurgere_inordine(TREE*, int*, int*);

int*    interclasare(int*, int*, int*, int);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    TREE* first  = NULL;
    TREE* second = NULL;
    TREE* final  = NULL;

    int size_first, size_second; fscanf(f_in, "%d", &size_first);
    for(int i = 0; i<size_first; i++) {
        int number; fscanf(f_in, "%d", &number);
        first = create_tree(first, number);
    }

    int* in_order_first = get_array(first, size_first);

    fscanf(f_in, "%d", &size_second);
    for(int i = 0, number; i<size_second; i++) {
        fscanf(f_in, "%d", &number);
        second = create_tree(second, number);
    } fclose(f_in);

    int* in_order_second = get_array(second, size_second);

    int  aux_size = size_first + size_second;
    int  final_size_array = 0;
    int* final_tree_array = interclasare(in_order_first, in_order_second, &final_size_array, aux_size);


    for(int i = 0; i<final_size_array; i++) {
        final = create_tree(final, final_tree_array[i]);
    }
    
    fprintf(f_out, "Arborele rezultat, parcurs in inordine: ");
    display_inorder(final, f_out);
    fclose(f_out);

    free(in_order_first);       in_order_first = NULL;
    free(in_order_second);      in_order_second = NULL;
    free(final_tree_array);     final_tree_array = NULL;
    deallocate_tree(first);     first  = NULL;
    deallocate_tree(second);    second = NULL;
    deallocate_tree(final);     final  = NULL;

    printf("Compiled in %0.3f seconds.\n", clock()*1.0/CLOCKS_PER_SEC);

    return 0;
}

TREE* create_node(int key) {
    TREE* new_node  =   (TREE*)calloc(1,sizeof(TREE));
    new_node->key   =   key;
    new_node->left  =   NULL;
    new_node->right =   NULL;
    return new_node;
}

TREE* create_tree(TREE* root, int key) {
    if(root == NULL) {
        return create_node(key);
    } else {
        if(key < root->key) root->left  = create_tree(root->left, key);
        if(key > root->key) root->right = create_tree(root->right, key);

        return root;
    }
}

void parcurgere_inordine(TREE* tree, int* arr, int* index) {
    if(tree == NULL) {
        return;
    }

    parcurgere_inordine(tree->left, arr, index);
    arr[*index] = tree->key;
    (*index)++;
    parcurgere_inordine(tree->right, arr, index);
}

int* get_array(TREE* tree, int size) {
    int index = 0;
    int* in_order_first = (int*)calloc(size,sizeof(int));
    parcurgere_inordine(tree, in_order_first, &index);
    return in_order_first;
}

int get_height(TREE* tree) {
    if(tree == NULL) return -1;
    return 1 + get_height(tree->left) + get_height(tree->right);
}

void display_inorder(TREE* tree, FILE* f) {
    if(tree == NULL) {
        return;
    }

    display_inorder(tree->left, f);
    fprintf(f, "%d ", tree->key);
    display_inorder(tree->right, f);
}

int*  interclasare(int first[], int second[], int* size, int aux_size) {

    int first_iterator  = 0;
    int second_iterator = 0;
    (*size) = 0;
    int* final_tree_array = (int*)calloc(aux_size, sizeof(int));
    for(int i = 0; i<aux_size; i++) {
        final_tree_array[(*size)++] = (first[first_iterator] < second[second_iterator] ? first[first_iterator++] : second[second_iterator++]);
    }

    return final_tree_array;
}

void deallocate_tree(TREE* tree) {
    if(tree==NULL) return;
    else {
        deallocate_tree(tree->left);    tree->left  = NULL;
        deallocate_tree(tree->right);   tree->right = NULL;
        free(tree);                     tree = NULL;
    }
}