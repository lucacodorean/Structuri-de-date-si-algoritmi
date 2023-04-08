#include <stdlib.h>
#include <stdio.h>
#include "arbore.h"

NodeT* createNode(int key) {

    NodeT* new_node = (NodeT*)calloc(1,sizeof(NodeT));
    new_node->key = key;
    new_node->left = new_node->right = NULL;
    return new_node;
}

NodeT* read_from_file(FILE* path) {

    if(path==NULL) {
        printf("Eroare la deschiderea fisierului.");
        return NULL;
    }

    char buffer[100]; 
    fscanf(path, "%s", buffer);

    if(buffer[0] == SENTINELA)  {
        return NULL;
    }

    int root;
    sscanf(buffer, "%d", &root);
        
    NodeT* new_node = createNode(root);
    new_node->left = read_from_file(path);
    new_node->right = read_from_file(path);

    return new_node;
}

void in_order(NodeT* root) {        /// SRD
    if(root == NULL) {
        return;
    }

    in_order(root->left);
    printf("%d ", root->key);
    in_order(root->right);
}

void post_order(NodeT* root) {     /// SDR 
    if(root == NULL) return;

    pre_order(root->left);
    pre_order(root->right);
    printf("%d ", root->key);
}

void pre_order(NodeT* root) {       ///RSD
    if(root == NULL) return;

    printf("Adr: %p, | Value: %d", root, root->key);
    pre_order(root->left);
    pre_order(root->right);
}

int leaf_node(NodeT* root) {
    if(root == NULL) return 0;

    if(root->left == NULL && root->right == NULL) {
        printf("Frunza identificata: %d.\n", root->key);
        return 1;
    } else return leaf_node(root->left) + leaf_node(root->right);
}

int internal_nodes(NodeT* root) {
    if(root == NULL) return 0;

    if(root->left != NULL || root->right != NULL) {
        printf("Nod intern identificat: %d.\n", root->key);
        return 1 + internal_nodes(root->left) + internal_nodes(root->right);
    } 
    else if(root->left == NULL && root->right == NULL) return 0;
}

int get_height(NodeT* root) {
    if(root == NULL) return -1;
    return max(get_height(root->left), get_height(root->right))+1;
}

void get_depth(NodeT* root, int prev_depth) {
    if(root == NULL) return;

    printf("\nAdr: %p | Value: %d | Depth: %d", root, root->key, prev_depth);
    prev_depth++;
    get_depth(root->left, prev_depth);
    get_depth(root->right, prev_depth);
}

NodeT* search(NodeT* root, int key) {
    if(root==NULL) {
        return NULL;
    }

    if(root->key == key) {
        printf("\nNodul %d a fost gasit. El are inaltimea %d.\n", root->key, get_height(root));
        return root;
    } else {
        NodeT* found_left = search(root->left, key);
        if(found_left != NULL) return found_left;
        
        NodeT* found_right = search(root->right, key);
        if(found_right != NULL) return found_right;
        
        else {
            printf("\nValoarea nu se gaseste in arbore.\n");
            return NULL;
        }
    }
}