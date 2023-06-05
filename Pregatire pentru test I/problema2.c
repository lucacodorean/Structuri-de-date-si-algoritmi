#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define SENTINELA        '#'
#define FILE_ERROR       400
#define MEMORY_ERROR     401
char operators[] = "+-*";

#ifndef __TREE__
    typedef struct _node {
        char character;
        struct _node* left;
        struct _node* right;
    } TREE;

    TREE*   create_node(char);
    TREE*   create_tree(FILE*);
    int     get_solution(TREE*);
    void    dealloc_tree(TREE*);
#endif

#ifndef __LIST__
    typedef struct _nodeL {
        TREE* item;
        struct _nodeL* next;
    } LIST;

    void    dealloc_list(LIST*);
    void    reverse_list(LIST**);
    LIST*   create_list_node(TREE*);
    void    create_list(LIST**, TREE*);
    void    add_to_list(LIST**, TREE*);
#endif

void operators_for_operands(TREE*, LIST*);

int main(void) {

    FILE* f_in = fopen("input2.in", "r");

    if(f_in == NULL) {
        printf("Eroare la prelucrarea fisierului de intrare.");
        exit(FILE_ERROR);
    }

    TREE* expression = create_tree(f_in);
    fclose(f_in); f_in = NULL;

    int result = get_solution(expression);
    printf("Rezultatul expresiei este: %d.\n", result);

    LIST* nodes_order = NULL;
    create_list(&nodes_order, expression);
    reverse_list(&nodes_order);
    operators_for_operands(expression, nodes_order);

    dealloc_tree(expression);
    dealloc_list(nodes_order);
    printf("\nCompiled in: %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);

    return 0;
}

TREE* create_node(char value) {
    TREE* new_node = (TREE*)calloc(1,sizeof(TREE));
    new_node ->character = value;
    new_node->left=new_node->right = NULL;
    return new_node;
}

TREE* create_tree(FILE* f) {

    char filter; 
    fscanf(f, "%c", &filter);
    if(filter == SENTINELA) {
        return NULL;
    }


    TREE* new_node = create_node(filter);
    if(new_node == NULL) {  
        printf("Eroare la alocarea memoriei.");
        return NULL;
    }

    /*  Apar doua cazuri, daca caracterul este operator sau operand.
            Daca avem operand, atunci inseamna ca nu mai 
            putem lega un operator de el, ca si fiu.
    */

    if(strchr(operators, filter) == NULL) {
        new_node = create_node(filter);
        return new_node;
    }

    new_node->left = create_tree(f);
    new_node->right = create_tree(f);

    return new_node;
}

LIST* create_list_node(TREE* tree) {
    LIST* new_node = calloc(1,sizeof(LIST));
    new_node->item = tree;
    new_node->next = NULL;
    return new_node;
}

void reverse_list(LIST** list) {
    LIST* prev = NULL;
    LIST* next = NULL;
    LIST* aux  = *list;

    while(aux != NULL) {
        next = aux->next;
        aux->next = prev;
        prev = aux;
        aux = next;
    }

    *list = prev;
}

void display_until_node(LIST* list, TREE* tree) {
    LIST* temp = list;
    if(temp == NULL || tree == NULL) return;
    else {
        while(temp != NULL) {
            if(temp->item == tree) break;
            else {
                
                if(strchr(operators, temp->item->character)) {
                    printf("%c ", temp->item->character);
                    //printf("\n\t %p | %c", temp->item, temp->item->character);
                }
                temp = temp->next;
            }
        }
    }
}

void operators_for_operands(TREE* tree, LIST* list) {
    if(tree==NULL) return;

    if(strchr(operators, tree->character)==NULL) {
        printf("\nPentru operandul %c se aplica: ", tree->character);
        LIST* temp = list;
        display_until_node(temp, tree);
    }

    operators_for_operands(tree->left, list);
    operators_for_operands(tree->right, list);
}

void create_list(LIST** list, TREE* tree) {
    if(tree==NULL) return;

    LIST* new_node = create_list_node(tree);
    if(*list==NULL) {
        *list = new_node;
    } else {
        new_node->next = *list;
        *list = new_node;
    }

    create_list(list, tree->left);
    create_list(list, tree->right);
}

int get_solution(TREE* tree) {
    if(strchr(operators, tree->character)==NULL) return (int)(tree->character-'0');

    int op1 = get_solution(tree->left);
    int op2 = get_solution(tree->right);

    if(tree->character == '+') return op1+op2;
    if(tree->character == '-') return op1-op2;
    if(tree->character == '*') return op1*op2;
}

void dealloc_tree(TREE* parameter) {
    if(parameter == NULL) return;

    dealloc_tree(parameter->left);    
    dealloc_tree(parameter->right);   
    free(parameter); parameter = NULL;
}

void dealloc_list(LIST* parameter) {
    if(parameter == NULL) return;
    dealloc_list(parameter->next);
    free(parameter);    
    parameter = NULL;
}