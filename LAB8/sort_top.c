#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
    int key;
    struct _node* next;
} NodeT;

NodeT* create_node(int);
void print_list(NodeT*, FILE*);
void add_to_list(NodeT**, int);
void dealloc_list(NodeT*);

#define NOT_VISITED 0
#define VISITED     1
#define HAS_CYCLE   1
#define NO_CYCLE    0

typedef struct {
    int vertexes_number;
    int edges_number;
    int *viz, *start, *finish;
    NodeT** adj;
} GRAPH;

GRAPH* init_graph(int);
void   init_adj_list(GRAPH*, FILE*);
int    DFS_cycle(int, GRAPH*);
int    has_cycle(GRAPH*);
void   DFS(int, GRAPH*, int*, NodeT**);
void   top_sort(GRAPH*, FILE*);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        return 0;
    }

    int size; fscanf(f_in, "%d", &size);
    GRAPH* my_graph = init_graph(size);
    init_adj_list(my_graph, f_in); fclose(f_in);

    if(has_cycle(my_graph)==NO_CYCLE) top_sort(my_graph, f_out);
    else fprintf(f_out, "Graful este ciclic.\nSortarea topologica nu este posibila.");

    fclose(f_out);
    printf("Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

NodeT* create_node(int key) {
    NodeT* new_node = (NodeT*)calloc(1,sizeof(NodeT));
    new_node -> key = key;
    new_node -> next = NULL;    
    return new_node;
}

void add_to_list(NodeT** list, int key) {
    NodeT* new_node = create_node(key);
    if(*list == NULL) {
        *list = new_node;
    } else {   
        new_node->next = *list;
        *list = new_node;
    }
}

void print_list(NodeT* list, FILE* path) {
    if(list == NULL) return;

    NodeT* temp = list;
    while(temp->next!=NULL) {
        fprintf(path, "%d ", temp->key);
        temp = temp->next;
    }
}

void dealloc_list(NodeT* list) {
    if(list == NULL) return;

    NodeT* temp = NULL;
    while(list != NULL) {
        temp = list;
        list = list->next;
        free(temp);
    }
}


GRAPH* init_graph(int size) {
    GRAPH* new_graph    = (GRAPH*)calloc(1,sizeof(GRAPH));
    new_graph->vertexes_number = size;
    new_graph->edges_number = 0;
    new_graph->viz      = (int*)calloc(size+1, sizeof(int));
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
}

void DFS(int current_vertex, GRAPH* my_graph, int* time, NodeT** list) {

    my_graph->start[current_vertex] = ++(*time);
    my_graph->viz[current_vertex] = VISITED;
    
    NodeT* temp = my_graph->adj[current_vertex];

    while(temp!=NULL) {
        if(my_graph->viz[temp->key] == NOT_VISITED) {
            DFS(temp->key, my_graph, time, list);
        }
        temp = temp->next;
    }

    add_to_list(list, current_vertex);
    my_graph->finish[current_vertex] = ++(*time);
}

int DFS_cycle(int current_vertex, GRAPH* graph) {
    if(graph->viz[current_vertex] == VISITED) return HAS_CYCLE;

    int cycle = NO_CYCLE;
    graph->viz[current_vertex] = VISITED;
    NodeT* adj_list = graph->adj[current_vertex];

    while(adj_list != NULL) {
        cycle = DFS_cycle(adj_list->key, graph);
        if(cycle == 1) return HAS_CYCLE;
        
        adj_list = adj_list->next;
    }
    
    return NO_CYCLE;
}

int has_cycle(GRAPH* graph) { 
    
    int cycle = NO_CYCLE;

    for(size_t i = 0; i<=(size_t)graph->vertexes_number; i++) {
        graph->viz[i] = NOT_VISITED;
    }

   for(size_t current_vertex = 1; current_vertex<=(size_t)graph->vertexes_number; current_vertex++) {
        graph->viz[current_vertex] = VISITED;
        
        NodeT* adj_list = graph->adj[current_vertex];

        while(adj_list != NULL) {
            cycle = DFS_cycle(adj_list->key, graph);      
            if(cycle == 1) return HAS_CYCLE;      
            adj_list = adj_list->next;
        }

        graph->viz[current_vertex] = NOT_VISITED;
    }

    return NO_CYCLE;
}

void top_sort(GRAPH* graph, FILE* path) {
    int time = 0;
    int no_parent = -1;


    for(size_t i = 0; i<=(size_t)graph->vertexes_number; i++) {
        graph->viz[i] = NOT_VISITED;
    }

    NodeT* sort_top = (NodeT*)calloc(1,sizeof(NodeT));
    for(size_t current_vertex = 1; current_vertex<=(size_t)graph->vertexes_number; current_vertex++) {
            if(graph->viz[current_vertex]==NOT_VISITED) DFS(current_vertex, graph, &time, &sort_top);
    }

    print_list(sort_top, path);
    dealloc_list(sort_top); sort_top = NULL;
}