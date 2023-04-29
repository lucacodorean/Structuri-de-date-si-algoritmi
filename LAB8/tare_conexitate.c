/*
    Definim tare conexitatea unui graf orientat ca pentru orice pereche de noduri (u,v) exista:
        a) un drum de la u la v; si
        b) un drum de la v la u.

    O componenta conexa a unui graf este tare conexa daca ea este un subgraf tare conex maximal, adica daca adaugam
    un nod nou in componenta curenta, isi pierde conexitatea.

    Pentru determinarea elementelor tare conexe, putem sa folosim algoritmul lui Kosaraju, un algoritm ce se bazezaza pe doua
    parcurgeri DFS. O parcurgere pe graful propriu-zis, si o a doua parcurgere pe grafului transpus.

    Algoritmul lui Kosaraju:
        - determinam transpusa grafului (G^t);
        - pentru G determinam timestamp-ul fiecarui nod (ne intereseaza in mare timpul de finalizare al parcurgerii);
        - parcurgem descrescator, in functie de timpii de finalizare, graful G^t, iar nodurile parcurse reprezinta o componenta tare conexa.


    Pentru determinarea tuturor elementelor tare conexe, vom face parcurgeri din toate varfurile nevizitate
    la finalizarea unei parcurgeri anterioare.

    Complexitatea este O(n+m) deoarece parcurge liniar toate varfurile si muchiile.
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 400
#define VISITED      1
#define NOT_VISITED  0

typedef struct _node {
    int key;
    struct _node* next; 
} NodeT;

NodeT* create_node(int);
void   add_to_list(NodeT**, int);

typedef struct {
    int vertexes_number, edges_number;
    int *visited;
    NodeT **adj_list, **adj_list_tr, *reversed_order;
} GRAPH;

GRAPH* init_graph(int);
void   init_graph_adj(GRAPH*, FILE*);
void   DFS(int, GRAPH*);
void   DFS_t(int, GRAPH*, FILE*);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    int size; fscanf(f_in, "%d ", &size);
    GRAPH* my_graph = init_graph(size);
    init_graph_adj(my_graph, f_in);

    for(size_t current_vertex = 1; current_vertex<=(size_t)my_graph->vertexes_number; current_vertex++) {
        if(my_graph->visited[current_vertex] == NOT_VISITED) DFS(current_vertex, my_graph);
    }

    int index = 0;
    for(size_t current_vertex = 1; current_vertex<=(size_t)my_graph->vertexes_number; current_vertex++) {
        my_graph->visited[current_vertex] = NOT_VISITED;
    }

    NodeT* temp = my_graph->reversed_order;

    while(temp->next!=NULL) {
        
        if(my_graph->visited[temp->key] == NOT_VISITED) {

            fprintf(f_out, "Componenta %d: ", ++index);
            DFS_t(temp->key, my_graph, f_out);
            fprintf(f_out, "\n");
        }
        temp = temp->next;
    }

    printf("Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);

    return 0;
}

NodeT* create_node(int key) {
    NodeT* new_node = (NodeT*)calloc(1,sizeof(NodeT));
    new_node->key   = key;
    new_node->next  = NULL;
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

GRAPH* init_graph(int size) {
    GRAPH* new_graph            = (GRAPH*)calloc(1,sizeof(GRAPH));
    new_graph->vertexes_number  = size;
    new_graph->edges_number     = 0;
    new_graph->visited          = (int*)calloc(new_graph->vertexes_number+1, sizeof(int));
    new_graph->reversed_order   = (NodeT*)calloc(1,sizeof(NodeT));
    new_graph->adj_list         = (NodeT**)calloc(new_graph->vertexes_number+1,sizeof(NodeT*));
    new_graph->adj_list_tr      = (NodeT**)calloc(new_graph->vertexes_number+1,sizeof(NodeT*));
    return new_graph;
}

void init_graph_adj(GRAPH* graph, FILE* path) {
    int u,v;
    while(fscanf(path, "%d %d", &u, &v)==2) {
        graph->edges_number++;
        add_to_list(&graph->adj_list[u], v);            /// aici se formeaza adiacenta pentru graful normal
        add_to_list(&graph->adj_list_tr[v], u);         /// aici se formeaza adiacenta pentru graful transpus.
    }
}

void DFS(int current_vertex, GRAPH* graph) {
    /// ce se intampla la intrarea in apel (start)
    graph->visited[current_vertex] = VISITED;
    NodeT* adj_node = graph->adj_list[current_vertex];

    while(adj_node!=NULL) {
        if(graph->visited[adj_node->key] == NOT_VISITED) DFS(adj_node->key, graph);
        adj_node = adj_node->next;
    }

    /// ce se intampla la finalizarea apelului (stop)
    add_to_list(&graph->reversed_order, current_vertex);
}

void DFS_t(int current_vertex, GRAPH* graph, FILE* path) {
    graph->visited[current_vertex] = VISITED;
    NodeT* adj_node = graph->adj_list_tr[current_vertex];

    fprintf(path, "%d ", current_vertex);

    while(adj_node!=NULL) {
        if(graph->visited[adj_node->key] == NOT_VISITED) DFS_t(adj_node->key, graph, path);
        adj_node = adj_node->next;
    }
}