#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int key;
    struct node* next;
} LIST;

LIST* create(int given_key) {
    LIST* new_node = (LIST*)calloc(1,sizeof(LIST));
    new_node->key = given_key;
    new_node->next = NULL;
    return new_node;
}

void link_to_list(LIST** head, int given_value) {
    LIST* new = create(given_value);
    if(head==NULL) {
        *head = new;
    } else {
        new->next = *head;
        *head = new;
    }
}

void print_list(LIST* head) {
    while(head!=NULL) {
        printf("%d ", head->key);
        head = head->next;
    }
}

int search(LIST* stack, int given_key) {
    while(stack!=NULL) {
        if(stack->key == given_key) return 1;
        stack = stack->next;
    }
    return 0;
}

int find_duplicate(LIST* head, LIST* stack) {
    int result = 0;
    while(head != NULL) {
        for(LIST* list = head->next; list != NULL; list = list->next) {
            if(list->key == head->key && search(stack, list->key)==0) {
                result++;
                link_to_list(&stack, list->key);
                break;
            }
        }
        head = head->next;
    }
    return result;
}


int main(void) {
    LIST* first = NULL;
    LIST* stack = NULL;

    link_to_list(&first, 1);
    link_to_list(&first, 7);
    link_to_list(&first, 23);
    link_to_list(&first, 3);
    link_to_list(&first, 2);
    link_to_list(&first, 7);
    link_to_list(&first, 7);
    link_to_list(&first, 3);

    printf("%d", find_duplicate(first, stack));

    free(first); first = NULL;
    return 0;
}