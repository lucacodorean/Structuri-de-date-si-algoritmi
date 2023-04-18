#include <stdlib.h>
#include <stdio.h>


typedef struct Node {
    int key;
    struct Node* next;
} LIST;


LIST* create_node(int);
void print_list(LIST*);
void reverse_list(LIST**);
void add_to_list(LIST**, LIST**, int);


int main(void) {
    LIST* list = NULL;
    LIST* tail = NULL;

    add_to_list(&list,&tail,3);
    add_to_list(&list,&tail,7);
    add_to_list(&list,&tail,7);
    add_to_list(&list,&tail,2);
    add_to_list(&list,&tail,3);
    add_to_list(&list,&tail,26);
    add_to_list(&list,&tail,7);
    add_to_list(&list,&tail,1);


    reverse_list(&list);
    print_list(list);

    free(list); list = NULL;
    free(tail); list = NULL;
    return 0;
}

LIST* create_node(int given_value) {
    LIST* new_node = (LIST*)calloc(1,sizeof(LIST));
    new_node->key = given_value;
    new_node->next = NULL;
    return new_node;
}

void add_to_list(LIST** head, LIST** tail, int given_value) {
    LIST* new_node = create_node(given_value);
    if(*head==NULL) *head = new_node;
    else (*tail)->next = new_node;

    *tail = new_node;
}

void print_list(LIST* list) {
    while(list!=NULL) {
        printf("%d ", list->key);
        list = list->next;
    }
}

void reverse_list(LIST** list) {
    LIST* prev = NULL;
    LIST* head = *list;
    LIST* next = NULL;
    while(head != NULL) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }

    *list = prev;
    return;
}