/**
 * @file biconexitate.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief  Sa se determine punctele de articulatie intr-un graf neorientat.
 *           Folosim un algoritm destul de basic, o matrice de adiacenta de pe care scoatem nodul curent si verificam daca subgraful obtinut este in conex.
 *           Daca subgraful obtinut in urma eliminarii nodului nu e conex, atunci nodul in cauza sa numeste punct de articulatie.
 * @version 0.1
 * @date 2023-05-04
 * 
 * @copyright Copyright (c) 2023
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define FILE_ERROR 400
#define VISITED      1
#define NOT_VISITED  0

typedef struct _node {
    int vertexes_number;
    int *visited, **adj_matrix;
} GRAPH;

GRAPH*  init_graph(int);
void init_adj_matrix(GRAPH*, FILE*);
void dealloc_graph(GRAPH*);

void DFS(int, GRAPH*);

int main(void) {
    FILE* f_in = fopen("data.in","r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in == NULL || f_out == NULL) {
        printf("FILE ERROR: Eroare la deschiderea fisierelor de I/O.");
        return FILE_ERROR;
    }

    int size, printed = 0; fscanf(f_in, "%d", &size);
    GRAPH* my_graph = init_graph(size);

    init_adj_matrix(my_graph, f_in); 
    fclose(f_in); f_in = NULL;

    for(int current_vertex = 1; current_vertex <= my_graph->vertexes_number; current_vertex++) {
        int* adj_nodes = (int*)calloc(my_graph->vertexes_number,sizeof(int));
        int l = 0, ok = 0;

        for(int adj_vertex = 1; adj_vertex <= my_graph->vertexes_number; adj_vertex++) {
            if(my_graph->adj_matrix[current_vertex][adj_vertex] == 1) {
                my_graph->adj_matrix[current_vertex][adj_vertex] = 0;
                my_graph->adj_matrix[adj_vertex][current_vertex] = 0;
                adj_nodes[++l] = adj_vertex;
            } else continue;
        }

        for(int i = 1; i <= my_graph->vertexes_number; i++) my_graph->visited[i] = NOT_VISITED;

        DFS(current_vertex == 1 ? 2 : 1, my_graph);
        for(int i = 1; i <= my_graph->vertexes_number && ok != 1; i++) {
            if(my_graph->visited[i] == NOT_VISITED && i != current_vertex) {
                ok = 1;
            }
        }

        if(ok == 1) {
            fprintf(f_out, "%d ", current_vertex);
            printed = 1;
        }

        for(int adj_vertex = 1; adj_vertex<=l; adj_vertex++) {
            my_graph->adj_matrix[current_vertex][adj_nodes[adj_vertex]] = 1;
            my_graph->adj_matrix[adj_nodes[adj_vertex]][current_vertex] = 1;
        }

        free(adj_nodes); adj_nodes = NULL;
    }

    if(!printed) fprintf(f_out, "%s", "Nu exista puncte de articulatie in graf.");
    dealloc_graph(my_graph);
    fprintf(f_out, "\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    fclose(f_out); f_out = NULL;
    return 0;
}

GRAPH* init_graph(int size) {
    GRAPH* my_graph = (GRAPH*)calloc(1,sizeof(GRAPH));
    my_graph->vertexes_number = size;
    my_graph->visited = (int*)calloc(size,sizeof(int));
    my_graph->adj_matrix = (int**)calloc(size+1, sizeof(int*));

    for(int vertex = 1; vertex<=my_graph->vertexes_number; vertex++) my_graph->adj_matrix[vertex] = (int*)calloc(size+1, sizeof(int));
    return my_graph;
}

void init_adj_matrix(GRAPH* graph, FILE* path) {
    int x, y;
    while(fscanf(path, "%d %d", &x, &y) == 2) {
        graph->adj_matrix[x][y] = 1;
        graph->adj_matrix[y][x] = 1;
    }
}

void dealloc_graph(GRAPH* graph) {
    for(int vertex = 0; vertex<=graph->vertexes_number; vertex++) {
        free(graph->adj_matrix[vertex]); graph->adj_matrix[vertex] = NULL;
    }

    free(graph); graph = NULL;
}

void DFS(int start, GRAPH* graph) {
    graph->visited[start] = VISITED;

    for(int adj_vertex = 1; adj_vertex <= graph->vertexes_number; adj_vertex++) {
        if(graph->adj_matrix[start][adj_vertex] == 1) {
            if(graph->visited[adj_vertex] == NOT_VISITED) DFS(adj_vertex, graph);
        }
    }
}