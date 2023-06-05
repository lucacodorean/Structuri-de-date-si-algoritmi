#include <stdio.h>
#include <stdlib.h>

typedef struct _node {
    int value;
    struct _node* next;
} Node;


Node* create_node(int value) {
    Node* new_node = (Node*)calloc(1,sizeof(Node));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

void demo(Node** node, int value) {
    Node* new_node = create_node(value);
    new_node->next = new_node;
    if(*node == NULL) *node = new_node;
    else {
        new_node->next = (*node)->next;
        (*node)->next = new_node;
        *node = new_node;
    }
    return;
}

int main(void) {
    Node* list = NULL;
    demo(&list, 20);
    demo(&list, 123);
    demo(&list, 14);
    demo(&list, -5);
    demo(&list, 8);
    demo(&list, 21);
    demo(&list, 143);
    demo(&list, 99);

    int displayed = 0;
    while(displayed != 8) {
        printf("%d ", list->value);
        list = list->next;
        displayed++;
    }
    return 0;
}