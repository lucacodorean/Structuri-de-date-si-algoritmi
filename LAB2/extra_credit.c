/**
 * @file extra_credit.c
 * @author Luca-Andrei Codorean
 * @brief  Se cere implementarea unei functii care face reverse la o lista simplu inlantuita.
 * @version 0.1
 * @date 2023-03-28
 * 
 * @copyright Copyright (c) 2023
**/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct node {
    int key;
    struct node* next;
} NodeT;

NodeT*  create_node(int);                                                       /// functia care va aloca memorie in heap pentru un nou nod
void    add_node_to_list(NodeT**, NodeT**, int);                                /// functia va functia pe principiul insert_last
void    reverse_linked_list(NodeT**);                                           /// functia care se va ocupa prorpiu-zis de inversare
void    display_list(NodeT*);                                                   /// functia care va afisa lista


int main(void) {
    NodeT* head = NULL;
    NodeT* tail = NULL;

    add_node_to_list(&head, &tail, 1);
    add_node_to_list(&head, &tail, 2);
    add_node_to_list(&head, &tail, 3);
    add_node_to_list(&head, &tail, 4);

    display_list(head);

    reverse_linked_list(&head);

    puts("\nDupa inversare:");
    display_list(head);

    printf("\nCompiled in: %0.3f seconds", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}


NodeT* create_node(int given_key) {                                          
    NodeT* new_node = (NodeT*)calloc(1,sizeof(NodeT));
    new_node->key = given_key;
    new_node->next = NULL;
    return new_node;
}

void add_node_to_list(NodeT** head, NodeT** tail, int given_key) { 
    NodeT* new_node = create_node(given_key);
    if(*head==NULL) {
        *head = new_node;
    } else {
        (*tail)->next = new_node;
    }

    *tail = new_node;
}


void reverse_linked_list(NodeT** head) {
    /**
     * @brief Inversarea unei liste simplu intalntuite presupune o "intoarcere" a elementelor listei, astfel tail-ul devine head, etc.
     * Intrucat functia nu aduce modificari fizice (gen marime) listei, ea este de tipul void. 
     * Pentru aceasta, vom avea nevoie de doi pointeri, respectiv unul auxiliar.
     * 
     *      Pentru a retine elementul la care ne deplasam dupa elementul curent, il salvam in next.
     *      Pentru a intoarce lista, elementul urmator elementului curent este elementul din urma elementului curent.
     *      Pentru a urmatorul element, elementul din urma este elementul la care ne aflam acum.
     *      Odata modificati actualizati acesti pointeri, putem sa trecem la urmatorul element din lista, salvat in next.
    **/

    NodeT* next = NULL;
    NodeT* prev = NULL;
    NodeT* aux = *head;

    while(aux != NULL) {
        next = aux->next;
        aux->next = prev;
        prev = aux;
        aux = next;
    }

    *head = prev;
}

void display_list(NodeT* head) {
    while(head!=NULL) {
        printf("\tAdr: %p | Val: %d\n", head, head->key);
        head = head->next;
    }
}
