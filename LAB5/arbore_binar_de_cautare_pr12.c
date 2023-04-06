#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_ERROR   404
#define TEXT_MAX_SIZE 256

typedef struct _node {
    char* key;
    struct _node* left;
    struct _node* right;
} TREE;

TREE* create_node(char*);
TREE* find_key(TREE*, char*);
TREE* create_tree(TREE*, char*);
void  parcurgere_preordine(TREE*, FILE*);
void  parcurgere_inordine(TREE*,  FILE*);

/*
    Pentru stergere, folosim doua functii, una care gaseste nodul cu cheia minima, respectiv una care
    face stergerea propriu-zisa.
*/

TREE* find_min_node(TREE*);
TREE* delete_node(TREE*, char*);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    TREE* my_tree = NULL;   

    int size; fscanf(f_in, "%d", &size);
    for(int i = 0; i<size; i++) {
        char* buffer = (char*)calloc(TEXT_MAX_SIZE, sizeof(char));
        fscanf(f_in, "%s", buffer);
        my_tree = create_tree(my_tree, buffer);
        free(buffer);
    } fclose(f_in);

    char* word = (char*)calloc(TEXT_MAX_SIZE, sizeof(char));
    scanf("%s", word);

    TREE* to_be_checked = find_key(my_tree, word); 
    if(to_be_checked == NULL) {
        printf("Cuvantul ``%s`` nu a fost gasit.\n", word);
    } else {
        printf("%p %s\n", to_be_checked, to_be_checked->key);
        my_tree = delete_node(my_tree, word);
    } free(word);

    parcurgere_preordine(my_tree, f_out); fclose(f_out);

    printf("Compiled in %0.3f seconds.", clock()*1.0 / CLOCKS_PER_SEC);
    return 0;
}

TREE* create_node(char* key) {
    TREE* new_node = (TREE*)calloc(1,sizeof(TREE));
    new_node->key  = (char*)calloc(strlen(key), sizeof(char));
    strcpy(new_node->key, key);
    new_node ->left = new_node ->right = NULL;
    return new_node;
} 

TREE* create_tree(TREE* root, char* key) {
    if(root == NULL) return create_node(key);
    else {
        if(strcmp(key, root->key) < 0)      root->left  = create_tree(root->left, key);
        else if(strcmp(key, root->key) > 0) root->right = create_tree(root->right, key);

        return root;
    }
}

void parcurgere_inordine(TREE* tree, FILE* f_out) {
    if(tree == NULL) return;

    parcurgere_inordine(tree->left, f_out);
    fprintf(f_out, "%s\n", tree->key);
    parcurgere_inordine(tree->right, f_out);
}

void parcurgere_preordine(TREE* tree, FILE* f_out) {
    if(tree == NULL) return;

    fprintf(f_out, "%s\n", tree->key);
    parcurgere_inordine(tree->left, f_out);
    parcurgere_inordine(tree->right, f_out);
}

TREE* find_key(TREE* tree, char* key) {
    if(tree == NULL) return NULL;
    if(strcmp(key, tree->key) == 0) return tree;
    else {
        TREE* temp = NULL;
        if(strcmp(key, tree->key) < 0) temp = find_key(tree->left, key);
        else if(strcmp(key, tree->key) > 0) temp = find_key(tree->right, key);

        return temp;
    }
}

TREE* find_min_node(TREE* tree) {
    if(tree == NULL) {
        return NULL;
    } else {
        TREE* temp = tree;
        while(temp->left!=NULL) {
            temp = temp->left;
        }
        tree = temp;
    }
}

TREE* delete_node(TREE* tree, char* key) {
    if(tree == NULL) return NULL;
    if(strcmp(key, tree->key) == 0) {
        /*
            Tratam doua cazuri: 1) avem un singur fiu;
                                2) avem doi fii;
        */

        TREE* temp = NULL;

        if(tree->left == NULL) {
            temp = tree->right; 
            free(tree);
            return temp;
        }

        if(tree->right == NULL) {
            temp = tree->left; 
            free(tree);
            return temp;
        }

        temp = find_min_node(tree->right);
        tree->key = temp->key;
        tree->right = delete_node(tree->right, temp->key);
        return tree;

    } else {
        if(strcmp(key, tree->key) < 0)      tree->left  = delete_node(tree->left, key);
        else if(strcmp(key, tree->key) > 0) tree->right = delete_node(tree->right, key);
        return tree;
    }
}