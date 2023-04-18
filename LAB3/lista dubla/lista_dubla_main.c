#include <stdlib.h>
#include <stdio.h>
#include "lista_dubla.h"

int main(void) {
    DOUBLE_LINKED_LIST list = {NULL, NULL};

    insert_last(&list, 1);
    insert_last(&list, 3);
    insert_last(&list, 5);
    insert_last(&list, 7);

    display_reverse(list);

    return 0;
}
