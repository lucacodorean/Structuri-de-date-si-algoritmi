#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SENTINELA 0

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} NODE;

NODE* createNode(int);
NODE* createTree(FILE*);
void  parcurgere_inordine(NODE*);
void  dealloc_tree(NODE*);

void  get_numbers(NODE*,int*,int*);
int   get_sum(int*, int);

int main(void) {

    FILE* f_in = fopen("input.in", "r");

    NODE* my_tree = createTree(f_in);
    //parcurgere_inordine(my_tree);
    int* numbers = (int*)calloc(100,sizeof(int));
    int size = 0;

    get_numbers(my_tree, numbers, &size);
    int sum = get_sum(numbers, size);

    printf("%d", sum);
    dealloc_tree(my_tree);

    return 0;
}

NODE* createNode(int key) {
    NODE* new_node = (NODE*)calloc(1,sizeof(NODE));
    new_node->key = key;
    new_node->left = new_node->right = NULL;
    return new_node;
}

NODE* createTree(FILE* path) {
    int number;
    fscanf(path, "%d", &number);

    NODE* new_node = NULL;

    if(abs(number) > 1000) return NULL;

    if(number < SENTINELA) {
        new_node = createNode(number);
        return new_node;
    } else {
        new_node = createNode(number);
        new_node->left = createTree(path);
        new_node->right = createTree(path);
    }



    return new_node;
}

void parcurgere_inordine(NODE* tree) {
    if(tree == NULL) return;

    parcurgere_inordine(tree->left);
    printf("%d ", tree->key);
    parcurgere_inordine(tree->right);
}

void dealloc_tree(NODE* tree) {
    if(tree == NULL) return;

    dealloc_tree(tree->left); tree->left   = NULL; 
    dealloc_tree(tree->right); tree->right = NULL;
    free(tree); tree = NULL;
}

void get_numbers(NODE* tree, int* arr, int* size) {
    if (tree == NULL) return;
   
    get_numbers(tree->left, arr, size);
    (*size)++;
    arr[*size] = tree->key;
    get_numbers(tree->right, arr, size);
}

int get_sum(int* arr, int size) {
    int result = 0, ex_result = 0;
    for(int i = 1; i<=size; i++) {
        if(i%2 == 1) result = result - arr[i];
        else result = result + arr[i];
    }
    return result;
}