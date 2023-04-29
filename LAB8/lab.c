#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef struct _node{
    int key;
    struct _node* next;
} NodeT;

NodeT*  createnode(int);
void add_to_list(NodeT**, int);
void print_list(NodeT*);

#define NOT_VISITED 0
#define VISITED     1

typedef struct {
    int vertexes;
    int edges_number;
    NodeT** adj;
    int *viz, *start, *finish, *parent;
} GRAPH;

GRAPH* init_graph(int);
int    search(int*, int, int);
int    chain(int, int, GRAPH*);
void   init_adj_list(GRAPH*, FILE*);
void   DFS(int, int, GRAPH*, int*, FILE*);
void   print_chain(int, int, GRAPH*, FILE*);

int cycle(int, int, GRAPH*);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        return 0;
    }

    int size; fscanf(f_in, "%d", &size);
    GRAPH* my_graph = init_graph(size);
    init_adj_list(my_graph, f_in); fclose(f_in);

    int time = 0;
    int no_parent = -1;

    DFS(7, no_parent, my_graph, &time, f_out);
    DFS(6, no_parent, my_graph, &time, f_out);
    DFS(1, no_parent, my_graph, &time, f_out);


    printf("Introduceti valori pentru nodul de start si cel de stop.\n");
    int start, stop;
    scanf("%d %d", &start, &stop);
    int result = chain(start, stop, my_graph);
    
    if(result) {
        print_chain(start, stop, my_graph, f_out);
    } else fprintf(f_out, "Nu exista drum intre %d si %d, in graful salvat la adresa %p.", start, stop, my_graph);

    printf("Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

GRAPH* init_graph(int size) {
    GRAPH* new_graph    = (GRAPH*)calloc(1,sizeof(GRAPH));
    new_graph->vertexes = size;
    new_graph->edges_number = 0;
    new_graph->viz      = (int*)calloc(size+1, sizeof(int));
    new_graph->parent   = (int*)calloc(size+1, sizeof(int));
    new_graph->start    = (int*)calloc(size+1, sizeof(int));
    new_graph->finish   = (int*)calloc(size+1, sizeof(int));
    new_graph->adj      = (NodeT**)calloc(size+1,sizeof(NodeT*));
    return new_graph;
}

void   init_adj_list(GRAPH* my_graph, FILE* data_in) {
    int x,y;
    while(fscanf(data_in, "%d %d", &x, &y)==2) {
        add_to_list(&my_graph->adj[x], y);
        my_graph->edges_number++;
    }

    /*for(int i = 1; i<=my_graph->vertexes; i++) {
        printf("%d: ", i);
        print_list(my_graph->adj[i]);
        printf("\n");
    }*/
}

NodeT* createnode(int key) {
    NodeT* new_node = (NodeT*)calloc(1,sizeof(NodeT));
    new_node -> key = key;
    new_node -> next = NULL;    
    return new_node;
}

void add_to_list(NodeT** list, int key) {
    NodeT* new_node = createnode(key);
    if(*list == NULL) {
        *list = new_node;
    } else {   
        new_node->next = *list;
        *list = new_node;
    }
}

void print_list(NodeT* list) {
    if(list == NULL) return;

    NodeT* temp = list;
    while(temp!=NULL) {
        printf("%d ", temp->key);
        temp = temp->next;
    }
}

void DFS(int current_vertex, int parent_vertex, GRAPH* my_graph, int* time, FILE* path) {

    my_graph->start[current_vertex] = *(++time);
    my_graph->parent[current_vertex] = parent_vertex;
    my_graph->viz[current_vertex] = VISITED;
    
    NodeT* temp = my_graph->adj[current_vertex];

    while(temp!=NULL) {
        if(my_graph->viz[temp->key] == NOT_VISITED) {
            DFS(temp->key, current_vertex, my_graph, time, path);
        }
        temp = temp->next;
    }

    my_graph->finish[current_vertex] = *(++time);
}

int search(int* arr, int size, int value) {
    for(int i = 0; i<=size; i++) {
        if(i == value) return arr[i];
    }

    return -1;
}

int chain(int start, int stop, GRAPH* my_graph) {
    while(start!=stop) {
        int aux = search(my_graph->parent, my_graph->vertexes, stop);
        if(aux==-1) {
            return 0;
        }
        stop = aux;
    } 

    return 1;
}

void print_chain(int start, int stop, GRAPH* my_graph, FILE* path) {
    while(start!=stop) {
        int aux = search(my_graph->parent, my_graph->vertexes, stop);
        if(aux==-1) {
            return;
        }
        fprintf(path, "%d ", aux);
        stop = aux;
    } 
}

int cycle(int start, GRAPH* my_graph) {
    STACK* my_stack = (STACK*)calloc(1,sizeof(STACK));
    
}