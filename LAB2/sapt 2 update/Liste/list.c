#include "list.h"
#include <stdlib.h>
#include <stdio.h>

NodeT* create(int givenkey) {
    NodeT* new = (NodeT*)calloc(1, sizeof(NodeT));
    new->key = givenkey;
    new->next = NULL;
    return new;
}

void print_list(NodeT* head) {
    while(head!=NULL) {
        printf("%d ", head->key);
        head = head->next;
    }
}

NodeT* search(NodeT* head, int givenkey) {
    while(head!=NULL) {
        if(head->key == givenkey) break;
        head = head ->next;
    }
    return head;
}

void insert_first(NodeT** first, NodeT** last, int givenkey) {
    NodeT* new = create(givenkey);
    if(*first==NULL) {
        *first = new;
        *last = new;
    } else {
        new->next = *first;
        *first = new;
    }
}

void insert_last(NodeT** first, NodeT** last, int givenkey) {
    NodeT* new = create(givenkey);
    if(*first == NULL) {
        *first = new;
    }
    else {
        (*last)->next = new;  
    }
    *last = new;
}

void insert_after_key(NodeT** first, NodeT** last, int afterKey, int givenKey) {
    NodeT* copy = *first;
    while(copy!=NULL) {
        if(copy->key == afterKey) break;
        copy = (copy) -> next;
    }

    if(copy != NULL) {
        NodeT* new = create(givenKey);
        new -> next = copy->next;
        copy->next = new;
        
        if(copy == *last) {
            *last = new;
        }
    }
}

void delete_first(NodeT** first, NodeT** last) {
    if(*first != NULL) {
        NodeT* copy = *first;
        *first = (*first)->next;    
        free(copy);                             /// intucat e alocat dinamic, trebuie sa eliminam din lista.

        if(*first == NULL) {                    /// daca head-ul e null inseamna ca nu mai exista elemente, deci si last trebuie sa fie null.
            *last = NULL;
        }
    }   
}

void delete_last(NodeT** head, NodeT** tail) {
    if(*head==NULL) return;                     /// verificam daca lista nu e goala inital
    else if((*head)->next==NULL) {              /// se verifica daca nu are doar un element
        free(head);
        return;
    }

    NodeT* copy = *head;                        /// copia pentru parcurgerea listei
    NodeT* copy_ant = NULL;                     /// aici vom retine elementul anterior ultimului
    
    while(copy!=*tail) {                        /// inaintam spre final tinand cont de anterior
        copy_ant = copy;
        copy = copy->next;
    }

    if(copy == *head) {                     
        *head = *tail = NULL;   
    } else {    
        copy_ant->next = NULL;                  /// marcam ca urmatorul element dupa anteriorul
                                                /// celui final sa fie NULL, dupa care legam coada la el.
        *tail = copy_ant;
    }
    free(copy);                                 /// stergerea propriu-zisa a elementului
}

void delete_key(NodeT** head, NodeT** tail, int givenkey) {
    if(*head==NULL) return;
    else if((*head)->next == NULL) {
        free(head);
        return;
    }

    NodeT* copy = *head;
    NodeT* copy_ant = NULL;
    
    while(copy!=*tail) {                        /// parcurgem lista
        copy_ant = copy;                        /// salvam anteriorul
        if(copy->key == givenkey) {             /// ne oprim cand am identificat key-ul
            break;
        }
        copy = copy->next;
    }


    if(copy == *head) {
        *head = (*head)->next;
        if(*head == NULL) *tail = NULL;
    } else {
        copy_ant->next = copy->next;            /// setam urmatorul anteriorul ca fiind urmatorul elementului curent, sarind astfel peste elementul curent.
        if(copy == *tail) *tail = copy_ant;     /// verificam daca elementul curent nu este chiar ultimul, si daca da, il setam ultimul element ca fiind anteriorul sau.
    }
    free(copy);                                 /// stergerea propriu-zisa
}

void reverse(NodeT** first) {
    NodeT* head = &first;                       ///  pointer care ne va ajuta in parcurgere.
    NodeT* prev = NULL;                         ///  aici vom tine adresa elementului din fata elementului curent.
    NodeT* aux = NULL;                          ///  aici vom tine adresa elementului curent, insa temporar.

    while(head!=NULL) {                         ///  cat timp nu am ajuns la o valoare nula (in cazul nostru poate sa fie si finalul)
        aux = head;                             ///  vom salva adresa elementului curent.
        head->next = prev;                      ///  adresa de dupa elementul curent se face de fapt adresa de inainte, pentru a aparea ideea de inversare
        prev = head;                            ///  in urma intoarcerii, elementul de inainte chiar elementul curent.
        head = aux;                             ///  pentru a nu sari peste noduri, vom reveni in nodul curent.
    }

    head = prev;
    return;
}