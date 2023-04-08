#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_SIZE   512
#define FILE_ERROR 404
#define SENTINELA    0

typedef struct _node {
    int key;
    struct _node* left;
    struct _node* right;
} NODE;

int   get_size(FILE*);
int** get_matrix(FILE*, int);
void  dealloc_matrix(int**, int);
void  get_array(FILE*, int**, int);

void  inorder(NODE*);
NODE* create_node(int);
void  dealloc_tree(NODE*);
NODE* create_tree(FILE*);


int main(void) {

    FILE* f_in  = fopen("data.in", "r");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    int size = get_size(f_in);
    fclose(f_in);

    f_in = fopen("data.in", "r");
    int** matrix = get_matrix(f_in, size);

    FILE* f_aux  = fopen("array.inout", "w");
    get_array(f_aux, matrix, size);
    fclose(f_aux);

    dealloc_matrix(matrix, size);
    
    f_aux = fopen("array.inout", "r");
    NODE* tree = create_tree(f_aux);

    inorder(tree);

    dealloc_tree(tree);

    return 0;
}

int get_size(FILE* path) {
    int size = 0, number;
    while(fscanf(path, "%d", &number)) {
        size++;
    }

    return sqrt(size);
}

int** get_matrix(FILE* path, int size) {
    int** matrix = (int**)calloc(size,sizeof(int*));
    for(int i = 0; i<size; i++) {
        matrix[i] = (int*)calloc(size, sizeof(int));
        for(int j = 0; j<size; j++) {
            fscanf(path, "%d", &matrix[i][j]);
        }
    }

    return matrix;
}

void get_array(FILE* path, int** matrix, int size) {
    int* array = (int*)calloc(size*size, sizeof(int));

    int l = 0;
    int sus = 0, st = 0;
    int jos = size, dr = size;
    while(sus<jos) {
        for(int i = st; i<dr; i++) {
            array[l++] = matrix[sus][i];
        }
        sus++;
        for(int j = sus; j<jos; j++) {
            array[l++] = matrix[j][dr-1];
        }
        dr--;
    
        for(int i = dr-1; i>=st; i--) {
            array[l++] = matrix[jos-1][i];
        }
        jos--;

        for(int j = jos-1; j>=sus; j--) {
            array[l++] = matrix[j][st];
        }
        st++;
    }
    
    for(int i = 0; i<size*size; i++) fprintf(path, "%d ", array[i]);
}

void dealloc_matrix(int** arr, int size) {
    for(int i = 0; i<size; i++) {
        free(arr[i]); arr[i] = NULL;
    }

    free(arr); arr = NULL;
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
    if(buffer[0] == '0') return NULL;

    int number; sscanf(buffer, "%d", &number);

    NODE* tree  = create_node(number);
    tree->left  = create_tree(path);
    tree->right = create_tree(path);
    return tree;
}

void inorder(NODE* tree) {
    if(tree == NULL) return;

    printf("%d ", tree->key);
    inorder(tree->left);
    inorder(tree->right);
}

void dealloc_tree(NODE* tree) {
    if(tree == NULL) return;

    dealloc_tree(tree->left);  free(tree->left);    tree->left  = NULL;
    dealloc_tree(tree->right); free(tree->right);   tree->right = NULL;
    free(tree); tree = NULL;
}