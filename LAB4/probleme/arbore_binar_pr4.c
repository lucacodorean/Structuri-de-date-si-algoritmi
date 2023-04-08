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

NODE* create_node(int);
NODE* create_tree(FILE*);
void  deallocate_tree(NODE*);

int max(int, int);
int get_height(NODE*);
int get_diameter(NODE*);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare");
        return FILE_ERROR;
    }

    NODE* tree = create_tree(f_in); 
    fclose(f_in); f_in = NULL;

    int tree_diameter = get_diameter(tree);
    fprintf(f_out, "Diametrul este egal cu: %d.\n", tree_diameter);
    fprintf(f_out, "Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);

    fclose(f_out); f_out = NULL;
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

    NODE* new_node = create_node(number);
    new_node->left = create_tree(path);
    new_node->right = create_tree(path);

    return new_node;
}

void  deallocate_tree(NODE* tree) {
    if(tree == NULL) return;

    deallocate_tree(tree->left);    tree->left  = NULL;  
    deallocate_tree(tree->right);   tree->right = NULL;
    free(tree); tree = NULL;
}

int max(int first, int second) {
    return (first > second ? first : second);
}

int get_height(NODE* tree) {
    if (tree == NULL) return 0;
    return max(get_height(tree->left), get_height(tree->right)) + 1;
}

int get_diameter(NODE* tree) {
    /*  Definim diametrul ca fiind distanta dintre doua frunze, mai exact cel mai lung 
        drum dintre doua frunze.

        Vom calcula inaltimile pentru sub arborele stang si cel drept, ulterior recursiv, calculam
        diametrul pentru subarborele stang si drept.

        Avem 3 cazuri: 
            cazul in care diametrul maxim se afla in sub-arborele stang;
            cazul in care diametrul maxim se afla in sub-arborele drept;
            cazul in care frunzele se afla in sub-arbori diferiti;
                in acest caz, rezultatul este suma inaltimilor + 1.
    */

    if(tree == NULL) return 0;

    int inaltime_stanga = get_height(tree->left);
    int inaltime_dreapta = get_height(tree->right);

    int diametru_stanga = get_diameter(tree->left);
    int diametru_dreapta = get_diameter(tree->right);

    return max(inaltime_stanga + inaltime_dreapta + 1, max(diametru_dreapta, diametru_stanga));
}