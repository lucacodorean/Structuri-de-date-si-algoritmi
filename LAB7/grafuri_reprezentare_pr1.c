#include <time.h>
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**
    Singura diferenta intre graful orientat si cel neorientat, este ca la graful neorientat,
        punem in matricea de adiacenta si pe pozitia (x,y), si pe (y,x).
*/

#define FILE_ERROR 404
#define NOT_VISITED 0
#define VISITED     1

typedef struct {
    int size, edges_count;
    int** adjacency_matrix;
} GRAPH;

GRAPH*  init_graph(int);
void    dealloc_graph(GRAPH*);
void    breadth_first_search(FILE*, GRAPH*, int);
void    get_adjacency_matrix_for_undirected_graph(GRAPH*, FILE*);

int main(void) {
    
    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    int size; fscanf(f_in, "%d", &size);
    GRAPH* graph = init_graph(size);
    
    get_adjacency_matrix_for_undirected_graph(graph, f_in); fclose(f_in);
    breadth_first_search(f_out, graph, 1);                  fclose(f_out);

    dealloc_graph(graph); graph = NULL;

    printf("Compiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

GRAPH* init_graph(int size) {
    GRAPH* graph = calloc(1,sizeof(GRAPH));
    graph->size = size;
    graph->edges_count = 0;
    graph->adjacency_matrix = (int**)calloc(size+1, sizeof(int*));

    for(int i = 1; i<=size; i++) graph->adjacency_matrix[i] = (int*)calloc(size+1, sizeof(int));
    return graph;
}

void get_adjacency_matrix_for_undirected_graph(GRAPH* graph, FILE* path) {
    int x, y;
    while(fscanf(path, "%d %d", &x, &y)==2) {
        graph->edges_count++;
        graph->adjacency_matrix[x][y] = 1;
    }
}

void breadth_first_search(FILE* path, GRAPH* graph, int start_point) {
    
    int* visited = (int*)calloc(graph->size, sizeof(int));  /// calloc pune oricum 0, si in cazul meu not_visited = 0
    QUEUE* queue = (QUEUE*)calloc(1,sizeof(QUEUE));

    visited[start_point] = VISITED;
    enqueue(queue, start_point);
    while(!empty(queue)) {
        int front = dequeue(queue);
        fprintf(path, "%d ", front);
        /// operatii cu nodurile extrase...
        for(int current_vertex = 1; current_vertex<=graph->size; current_vertex++) {
            if(graph->adjacency_matrix[front][current_vertex] == 1) {
                if(visited[current_vertex] == NOT_VISITED) {
                    visited[current_vertex] = VISITED;
                    enqueue(queue,current_vertex);
                }
            } else continue;
        }
    }

    free(visited); visited = NULL;
    dealloc_queue(queue); queue = NULL;
}

void dealloc_graph(GRAPH* graph) {
    for(int i = 0; i<=graph->size; i++) {
        free(graph->adjacency_matrix[i]); graph->adjacency_matrix[i] = NULL;
    }

    free(graph->adjacency_matrix); graph->adjacency_matrix = NULL;
}
