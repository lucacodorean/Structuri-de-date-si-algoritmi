#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FILE_ERROR  404
#define SENTINELA   INT_MIN

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} TREE;

TREE* create_node(int);
void  deallocate_tree(TREE*);
TREE* create_tree(TREE*, int);
void  display_inorder(TREE*, FILE*);
void  parcurgere_inordine(TREE*, int*, int*);

int* get_inorder_array(TREE*, int);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    TREE* my_tree = NULL;

    int number, size = 0;
    while(fscanf(f_in, "%d", &number) == 1) {
        my_tree = create_tree(my_tree, number);
        size++;
    } fclose(f_in);

    int x; scanf("%d", &x);
    int* numbers = get_inorder_array(my_tree, size);
    int ok = 0;

    display_inorder(my_tree, f_out);

    for(int i = 0; i<size; i++) {
        int number = numbers[i];
        for(int j = 0; j<size; j++) {
            if(j!=i) {
                if(numbers[j] + number == x && ok == 0) {
                    fprintf(f_out, "Exista doua numere care respecta cerinta. Ele sunt %d si %d.\n", number, numbers[j]);
                    ok = 1;
                    break;
                }
            }
        }
        if(ok == 1) break;
    }


    if(ok == 0) fprintf(f_out, "Nu exista numere care sa se incadreze in cerinta.");

    deallocate_tree(my_tree);

    printf("Compiled in %0.3f seconds.", clock()*1.0 / CLOCKS_PER_SEC);
    return 0;
}

TREE* create_node(int key) {
    TREE* new_node = (TREE*)calloc(1,sizeof(TREE));
    new_node -> key = key;
    new_node -> left = new_node -> right = NULL;
    return new_node;
}

TREE* create_tree(TREE* root, int key) {
    if(root == NULL) {
        return create_node(key);
    }
    else {
        if(key < root->key) root->left = create_tree(root->left, key);
        else if(key > root->key) root->right = create_tree(root->right, key);
        return root;
    }
}

void display_inorder(TREE* tree, FILE* path) {
    if(tree == NULL) return;
    
    display_inorder(tree->left, path);
    fprintf(path, "%d ", tree->key);
    display_inorder(tree->right, path);

}

int* get_inorder_array(TREE* my_tree, int size) {
    int index = 0;
    int* array =  (int*)calloc(size, sizeof(int));

    for(int i = 0; i<size; i++) array[i] = SENTINELA;

    parcurgere_inordine(my_tree, array, &index);
    return array;
}

void parcurgere_inordine(TREE* tree, int* array, int* index) {
    if(tree == NULL) return;
    
    parcurgere_inordine(tree->left, array, index);
    array[*index] = tree->key;
    (*index)++;
    parcurgere_inordine(tree->right, array, index);
}

void deallocate_tree(TREE* tree) {
    if(tree == NULL) return;

    deallocate_tree(tree->left);  tree->left = NULL;
    deallocate_tree(tree->right); tree->right = NULL;
    free(tree); tree = NULL;
}