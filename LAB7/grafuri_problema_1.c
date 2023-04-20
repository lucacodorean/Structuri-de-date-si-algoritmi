#include <time.h>
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define VISITED     1
#define NOT_VISITED 0

typedef struct _graph {
    int edges_number;
    int vertexes_number;
    int** matrix;
} GRAPH;

GRAPH*  create_graph(int size);
void    init_graph(GRAPH*, FILE*);
int     bfs(GRAPH*, int, int);
void    dealloc_graph(GRAPH*);

int main(void) {
    FILE* f_in = fopen("data.in", "r");

    int size; fscanf(f_in, "%d", &size);
    GRAPH* graph = create_graph(size);

    init_graph(graph, f_in);

    int starting_point, ending_point;
    printf("Introduceti nodul de pornire si noudl de plecare, dupa forma: nod_start nod_stop.: ");
    scanf("%d %d", &starting_point, &ending_point);
    int result = bfs(graph, starting_point, ending_point);
    printf("%sxista drum intre nodul %d, de start, si %d, de oprire.", (result==1 ? "E" : "Nu e"), starting_point, ending_point);

    dealloc_graph(graph);
    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

GRAPH* create_graph(int size) {
    GRAPH* new_graph = (GRAPH*)calloc(1,sizeof(GRAPH));
    new_graph->edges_number = 0;
    new_graph->vertexes_number = size;
    new_graph->matrix = (int**)calloc(size+1, sizeof(int*));

    for(int i = 1; i<=size; i++) new_graph->matrix[i] = (int*)calloc(size+1, sizeof(int));
    return new_graph;
}

void init_graph(GRAPH* my_graph, FILE* path) {
    if(path == NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return;
    }

    int x,y;
    while(fscanf(path, "%d %d", &x, &y) == 2) {
        my_graph->matrix[x][y] = 1;
        my_graph->edges_number++;
    }
}

int bfs(GRAPH* my_graph, int start_point, int end_point) {
    int* visited = (int*)calloc(my_graph->vertexes_number, sizeof(int));
    QUEUE* my_queue = (QUEUE*)calloc(1,sizeof(QUEUE));

    enqueue(my_queue, start_point);
    visited[start_point] = VISITED;

    while(!empty(my_queue)) {
        int front = dequeue(my_queue);
        
        if(end_point == front) return 1;

        for(int current_vertex = 1; current_vertex<=my_graph->vertexes_number; current_vertex++) {
            if(my_graph->matrix[front][current_vertex] == 1) {
                if(!visited[current_vertex]) {
                    enqueue(my_queue, current_vertex);
                    visited[current_vertex] = VISITED;
                }
            } else continue;
        }
    }

    free(visited); visited = NULL;
    dealloc_queue(my_queue); my_queue = NULL;
    return 0;
}

void dealloc_graph(GRAPH* my_graph) {
    for(int i = 0; i<=my_graph->vertexes_number; i++) {
        free(my_graph->matrix[i]); my_graph->matrix[i] = NULL;
    }

    free(my_graph->matrix); my_graph->matrix = NULL;
    free(my_graph);         my_graph = NULL;
}