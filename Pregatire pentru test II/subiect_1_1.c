/**
 * @file subiect_1_1.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief   Fisierul de input data.in contine datele unui graf neorientat dupa forma:
 *             * pe prima linie avem numarul de varfuri ale grafului;
 *             * pe urmatoarele n linii avem perechi de forma u-v, fapt ce semnifica muchie intre nodurile u si v;
 * 
 *          Se cere:
 *             * aplicarea algoritmului de parcurgere in adancime pe graful dat;
 *             * determinarea calitatii de arbore a grafului.
 * 
 * 
 *   Rezolvare: 
 *      Un graf neorientat se numeste arbore daca el este aciclic si conex. Deci, ar trebui sa verificam daca graful contine cicluri si daca este conex.
 *      Pentru ambele verificari vom folosi algoritmul DFS.
 * 
 * @version 0.1
 * @date 2023-05-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FILE_ERROR 400
#define VISITED      1
#define NOT_VISITED  0
#define HAS_CYCLE    1
#define NO_CYCLE     0

typedef struct _node {
    int value;
    struct _node* next;
} Node;

Node* create_node(int);
void add_to_list(Node**, int);

typedef struct {
    int vertexes_number; 
    int edges_number;
    int* visited;
    Node** adj_node;
} Graph;

Graph* create_graph(int);
int DFS(int, int, int*, Graph*);
int DFS_Call(int, int, Graph*);
void init_adj_node(Graph*, FILE*);


/// @brief Functia determina daca graful indicat ca si parametru contine un ciclu. 
///        Facem verificari din fiecare nod al grafului, folosind algoritmul DFS.
/// @param Graph*
/// @return HAS_CYCLE || NO_CYCLE
int has_cycle(Graph*);

int main(void) {

    FILE* data_in  = fopen("data.in", "r");
    FILE* data_out = fopen("data.out", "w");

    if(data_in == NULL || data_out == NULL) {
        perror("Error");
        return FILE_ERROR;
    }

    int size; fscanf(data_in, "%d", &size);
    Graph* graph = create_graph(size);
    init_adj_node(graph, data_in);

    int start_node = -1, parent = -1, ok = 0;
    while(ok ==  0) {
        printf("\nIntroduceti nodul din care doriti sa incepeti parcurgerea in adancime: ");
        scanf("%d", &start_node);
        if(start_node <= graph->vertexes_number) ok = 1;
        else printf("\tNodul %d nu apartine grafului. Va trebui sa introduceti un alt nod.", start_node);
    }

    int conex  = DFS_Call(start_node, parent, graph);
    int ciclic = has_cycle(graph); 

    printf("\nconex: %d ciclic: %d\n", conex, ciclic);

    fprintf(data_out, "Graful%s este un arbore.", (conex == 1 && ciclic == NO_CYCLE) ? "" : " nu"); fclose(data_out);
    
    printf("Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

Node* create_node(int value) {
    Node* new_node = (Node*)calloc(1,sizeof(Node));
    new_node->next = NULL;
    new_node->value = value;
    return new_node;
}

void add_to_list(Node** list, int value) {
    Node* new_node = create_node(value);

    if(*list == NULL) {
        *list = new_node;
        return;
    } else {
        new_node->next = *list;
        *list = new_node;
        return;
    }
}

Graph* create_graph(int size) {
    Graph* new_graph = (Graph*)calloc(1,sizeof(Graph));
    new_graph->vertexes_number = size;
    new_graph->edges_number = 0;

    new_graph->visited =  (int*)calloc(size+1, sizeof(int));
    new_graph->adj_node = (Node**)calloc(size+1, sizeof(Node*));
    return new_graph;
}

void init_adj_node(Graph* graph, FILE* path) {
    int x,y;
    while(fscanf(path, "%d-%d", &x, &y)==2) {
        if(x > graph->vertexes_number || y > graph->vertexes_number) {
            printf("\nMuchia %d-%d nu se poate adauga in graf.", x,y);
            continue;
        } else {
            graph->edges_number++;
            add_to_list(&graph->adj_node[x],y);
            add_to_list(&graph->adj_node[y],x);
        }
    }
    fclose(path);
}

int DFS(int node, int parent, int* len, Graph* graph) {
    graph->visited[node] = VISITED;
    (*len)++;

    printf("%d ", node);

    Node* adj_node = graph->adj_node[node];
    while(adj_node!=NULL) {
        if(graph->visited[adj_node->value] == NOT_VISITED) {
            if(DFS(adj_node->value, node, len, graph) == 1) return 1;
        } else if(adj_node->value != parent) return 1;                
        adj_node = adj_node->next;
    }
    return 0;                                                         
}

int DFS_Call(int node, int parent, Graph* graph) {
    int l = 0;

    for(int current_vertex = 0; current_vertex<=graph->vertexes_number; current_vertex++) graph->visited[current_vertex] = NOT_VISITED;
    DFS(node, parent, &l, graph);

    return l == graph->vertexes_number;
}

int has_cycle(Graph* graph) { 
    for(int current_vertex = 1, l = 0; current_vertex<=graph->vertexes_number; current_vertex++) {
        graph->visited[current_vertex] = NOT_VISITED;
    }
    int l = 0;
    return DFS(1,-1, &l, graph);
}