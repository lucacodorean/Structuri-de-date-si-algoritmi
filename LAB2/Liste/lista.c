#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CORRECTLY_COMPILED   0
#define FILE_ERROR         404
/*
    Daca lista declarata in semnatura functiei ca si pointer dublu,
    vom realiza o parcurgere folosind o copie a listei:
        NodeT *copy = ** first; -> primeste head-ul functiei.

*/


int main(void) {
    NodeT* first = NULL;
    NodeT* second = NULL;

    
    for(int i = 0; i<=20; i++) {
        insert_last(&first, &second, i);
    }
    
    delete_last(&first, &second);

    FILE* file = fopen("dest.bin", "wb");
    if(file==NULL) {
        printf("Eroare la crearea fisierului de scriere.");
        return FILE_ERROR;
    }

    while(first!=NULL) {
        fwrite(&(first->key), sizeof(int), 1, file);
        first = first->next;
    }

    printf("\nCompiled in: %0.3f seconds", clock()*1.0/CLOCKS_PER_SEC);

    fclose(file); 
    free(first);    first = NULL;
    free(second);   second = NULL;
    return CORRECTLY_COMPILED;
}
