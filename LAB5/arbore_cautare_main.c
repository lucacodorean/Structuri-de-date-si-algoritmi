#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} NodeT;

#define SENTINELA -1

NodeT* findMin(NodeT*);
NodeT* findMax(NodeT*);
NodeT* create_node(int);
NodeT* searchKey(NodeT*, int);
NodeT* insert_node(NodeT*, int);
NodeT* get_succesor(NodeT*, NodeT*);

void parcurgere_inordine(NodeT*);
void parcurgere_preordine(NodeT*);
void parcurgere_postordine(NodeT*);

int main(void) {
    NodeT* root = NULL;
    root = insert_node(root, 5);

    insert_node(root, 3);
    insert_node(root, 4);
    insert_node(root, 7);
    insert_node(root, 2);
    printf("\nINORDER: \t");    parcurgere_inordine(root);
    printf("\nPRENORDER: \t");  parcurgere_preordine(root);
    printf("\nPOSTNORDER: \t"); parcurgere_postordine(root);

    NodeT* min_node = findMin(root);
    printf("\n\tmin_node: %p | %d", min_node, min_node->key);

    NodeT* max_node = findMax(root);
    printf("\n\tmin_node: %p | %d", max_node, max_node->key);

    NodeT* searched_node = searchKey(root, 3);
    if(searched_node != NULL) printf("\n\tsearched_node: %p | %d", searched_node, searched_node->key);
    else printf("\nNu exista eticheta in arbore.");

    NodeT* succesor_node = get_succesor(root, searched_node);
    if(succesor_node != NULL) printf("\n\tsuccesor_node: %p | %d", succesor_node, succesor_node->key);
    return 0;
}

NodeT* create_node(int key_value) {
    NodeT* new_node = (NodeT*)calloc(1,sizeof(NodeT));

    new_node->key = key_value;
    new_node->left = new_node->right = NULL;

    return new_node;
}


NodeT* insert_node(NodeT* root, int key_value) {
    /// functia returneaza radacina arborelui dupa inserare.
    if(root==NULL) return create_node(key_value);
    else {
        if(key_value < root->key)       root->left  = insert_node(root->left, key_value);
        else if(key_value > root->key)  root->right = insert_node(root->right, key_value);

        return root;
    }
}

NodeT* findMin(NodeT* node) {
    if(node==NULL) return NULL;
    if(node->left == NULL) return node;
    else return findMin(node->left);
}

NodeT* findMax(NodeT* node) {
    if(node==NULL) return NULL;
    if(node->right == NULL) return node;
    else return findMax(node->right);
}

NodeT* searchKey(NodeT* root, int key_value) {
    if(root==NULL) return NULL;
    if(key_value == root->key) return root;
    else {
         if(key_value<root->key) {
            NodeT* left = searchKey(root->left, key_value);
            return left;
        } 
        if(key_value>root->key){
            NodeT* right = searchKey(root->right, key_value);
            return right;
        }
        
        return NULL;
    }
}

NodeT* get_succesor(NodeT* node, NodeT* root) {
    NodeT* succesor = NULL;
    if(node->right != NULL) succesor = findMax(node->left);             /// daca nodul are sub arbore stang, cautam maximul din sub arborele drept.
    if(node->right == NULL) {
        while(root!=node) {
            if(root->key < node->key)      succesor = root;            
            if(root->key > node->key)      root = root->left;
            else                           root = root->right;
        }
        
    }
    return succesor;
}

void parcurgere_inordine(NodeT* root) {
    if(root==NULL) return;

    parcurgere_inordine(root->left);
    printf("%d ", root->key);
    parcurgere_inordine(root->right);
}

void parcurgere_preordine(NodeT* root) {
    if(root == NULL) return;

    printf("%d ", root->key);
    parcurgere_preordine(root->left);
    parcurgere_preordine(root->right);
}

void parcurgere_postordine(NodeT* root) {
    if(root == NULL) return;

    parcurgere_postordine(root->left);
    parcurgere_postordine(root->right);
    printf("%d ", root->key);
}