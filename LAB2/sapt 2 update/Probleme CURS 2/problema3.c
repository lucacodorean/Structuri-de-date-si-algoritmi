#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int key; 
    struct node* next;
} NodeT;

NodeT* create(int);
NodeT* make_copy(NodeT*);

void print_list(NodeT*);
void search(NodeT*, int);
void add_to_list(NodeT**, NodeT**, int);

int main(void) {

    NodeT* list = NULL;
    NodeT* tail = NULL;

    add_to_list(&list,&tail,3);
    add_to_list(&list,&tail,7);
    add_to_list(&list,&tail,7);
    add_to_list(&list,&tail,2);
    add_to_list(&list,&tail,3);
    add_to_list(&list,&tail,26);
    add_to_list(&list,&tail,7);
    add_to_list(&list,&tail,1);

    search(list, 15);
    print_list(list);

    free(list); list = NULL;
    free(tail); tail = NULL;

    return 0;
}

NodeT* create(int given_value) {
    NodeT* new = (NodeT*)calloc(1,sizeof(NodeT));
    new->key = given_value;
    new->next = NULL;
    return new;
}

void search_and_replace(NodeT* list, int value) {
    NodeT* copy = NULL;
    NodeT* temp = list;
    while(temp!=NULL) {
        int cate = 0;
        copy = make_copy(list);
        while(copy!=NULL) {
            if(temp->key == copy->key) cate++;
            copy = copy->next;
        }

        if(cate == 1) temp->key = value;   
        temp = temp -> next;
    }

    free(copy); copy = NULL;
}

void add_to_list(NodeT** first, NodeT** last, int value) {
    NodeT* new = create(value);
    if(*first == NULL) *first = new;
    else (*last)->next = new; 
    *last = new;
}

void print_list(NodeT* list) {
    printf("\nElementele listei sunt:\n\t");
    while(list!=NULL) {
        printf("%d ", list->key);
        list = list->next;
    }
}

NodeT* make_copy(NodeT* list) {
    if(list == NULL) return NULL;
    
    NodeT* new = (NodeT*)calloc(1, sizeof(NodeT));
    new->key = list->key;
    new->next = make_copy(list->next);
    return new;
}

