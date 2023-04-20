#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"

#define FILE_ERROR 404
#define NOT_VISITED  0
#define VISITED      1

typedef struct {
    int size, edges_number;
    NODET** adjacency_list;
} GRAPH;

GRAPH* init_graph(int);
void   populate_adjacency_lists(FILE*, GRAPH*);
void   breadth_first_search(FILE*, GRAPH*, int);
void   dealloc_graph(GRAPH*);

int main(void) {

    FILE* f_in   = fopen("data.in", "r");
    FILE* f_out  = fopen("data.out", "w");

  
    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    int size; fscanf(f_in, "%d", &size);
    GRAPH* graph = init_graph(size);

    populate_adjacency_lists(f_in, graph);
    breadth_first_search(f_out, graph, 3);

    dealloc_graph(graph);
    printf("Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

GRAPH* init_graph(int size) {
    GRAPH* new_graph = (GRAPH*)calloc(1,sizeof(GRAPH));
    new_graph->size = size;
    new_graph->edges_number = 0;
    new_graph->adjacency_list = (NODET**)calloc(new_graph->size + 1,sizeof(NODET*));
    return new_graph;
}

void populate_adjacency_lists(FILE* path, GRAPH* graph) {
    int x,y;
    while(fscanf(path, "%d %d", &x, &y) == 2) {
        graph->edges_number ++;
        add_to_list(&graph->adjacency_list[x],y);
    }
}

void breadth_first_search(FILE* path, GRAPH* graph, int starting_point) {

    int* visited = (int*)calloc(graph->size, sizeof(int));
    QUEUE* queue = (QUEUE*)calloc(1,sizeof(QUEUE));

    visited[starting_point] = VISITED;
    enqueue(queue, starting_point);

    while(!empty(queue)) {
        int front = dequeue(queue);
        fprintf(path, "%d ", front);
        for(int current_vertex = 1; current_vertex<=graph->size; current_vertex++) {
            if(search(graph->adjacency_list[front], current_vertex)==1) {
                if(visited[current_vertex] == NOT_VISITED) {
                    visited[current_vertex] = VISITED;
                    enqueue(queue, current_vertex);
                }
            } else continue;
        }
    }

    free(visited);        visited = NULL;
    dealloc_queue(queue); queue   = NULL;
}

void dealloc_graph(GRAPH* graph) {
    for(int i = 0; i<=graph->size; i++) {
        dealloc_list(graph->adjacency_list[i]); 
    }

    free(graph); graph = NULL;
}