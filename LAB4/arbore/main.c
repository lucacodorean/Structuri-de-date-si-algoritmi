#include <stdio.h>
#include <stdlib.h>
#include "arbore.h"

#define FILE_ERROR 404

int main(void) {

    FILE* f = fopen("arbore.txt", "r");

    if(!f) {
        printf("Eroare la prelucararea fisierului.");
        return FILE_ERROR;
    }

    NodeT* root = read_from_file(f);
    printf("PARCURGERE IN PRE ORDINE:\n");
    pre_order(root); printf("\n");
    
    int leafs = leaf_node(root);
    printf("Arborele are %d frunze.\n\n", leafs);
    
    int internal_nodes_count = internal_nodes(root);
    printf("Arborele are %d noduri interne.\n\n", internal_nodes_count);
    printf("Inaltimea arborelui este: %d.", get_height(root));

    NodeT* found = search(root, 9);
    printf("Adr: %p : Value: %d", found, found->key);

    get_depth(root, 0);

    return 0;
}
