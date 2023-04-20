/// 
/**
 * @brief
 *      Sa se determine distanta minima dintre un punct de start si unul de stop.
 *      Folosim BFS, intrucat nu avem un graf cu ponderi. Pentru graful cu ponderi putem sa folosim algoritmul lui Dijkstra.
 *      Vom folosi un array alocat dinamic in care stocam distantele de la punctul de start pana la cel de final, ulterior functia de BFS returneaza
 *      distanta dintre punctul de start si cel de stop, adica distanta[stop].
 * 
 *      Am verificat si cazul in care exista arc de la un nod la el insusi, prin faptul ca am initializat vectorul de distante cu -1 si am marcat distanta startului
 *      cu 0.
 * 
 *      Pentru fiecare nod nevizitat, se calculeaza distanta astfel: distanta "radacinii nodului" + 1 (deseneaza arborele de parcurgere si vei intelege).
*/

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "queue.h"

#define FILE_ERROR 404
#define VISITED      1
#define NOT_VISITED  0
#define CHARACTERS_LIMIT_PER_SENTANCE 128
#define SENTINELA 9999

typedef struct _graph {
    int vertexes_number, edges_number;
    int** matrix;
} GRAPH;

GRAPH*  init_graph(int);
int     BFS(GRAPH, int, int);
void    dealloc_graph(GRAPH*);
void    get_matrix(GRAPH*, FILE*);
char*   display_distance(char*, int);

int main(void) {

    FILE* f_in = fopen("data.in", "r");
    FILE* f_out = fopen("data.out", "w");

    if(f_in==NULL) {
        printf("Eroare la deschiderea fisierului de intrare.");
        return FILE_ERROR;
    }

    int size; fscanf(f_in, "%d", &size);
    GRAPH* my_graph = init_graph(size);

    get_matrix(my_graph, f_in); fclose(f_in);

    int start_point, stop_point;
    printf("Introduceti nodurile de start si stop, dupa structura: start_point stop_point: ");
    scanf("%d %d", &start_point, &stop_point);

    int result = BFS(*my_graph, start_point, stop_point);
    char* display_text = (char*)calloc(CHARACTERS_LIMIT_PER_SENTANCE, sizeof(char));

    strcpy(display_text, (result != -1 ? display_distance(display_text, result) : "Nodurile nu fac parte din aceeasi componenta conexa."));
    printf("%s", display_text);

    fclose(f_out);
    dealloc_graph(my_graph);
    free(display_text); display_text = NULL;

    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

GRAPH* init_graph(int size) {
    GRAPH* new_graph = (GRAPH*)calloc(1,sizeof(GRAPH));
    new_graph->vertexes_number = size;
    new_graph->edges_number = 0;
    new_graph->matrix = (int**)calloc(size+1,sizeof(int*));
    for(int i = 0; i<=new_graph->vertexes_number; i++) new_graph->matrix[i] = (int*)calloc(size+1, sizeof(int));
    return new_graph;
}

void get_matrix(GRAPH* my_graph, FILE* path) {
    int x,y;
    while(fscanf(path, "%d %d", &x, &y) == 2) {
        my_graph->edges_number++;
        my_graph->matrix[x][y] = 1;
    }
}


int BFS(GRAPH my_graph, int start, int stop) {
    QUEUE*  queue        = (QUEUE*)calloc(1,sizeof(QUEUE));
    int*    visited     = (int*)calloc(my_graph.vertexes_number+1, sizeof(int));
    int*    distances   = (int*)calloc(my_graph.vertexes_number+1, sizeof(int));
    int     actual_distance = 0;

    for(int i = 0; i<=my_graph.vertexes_number; i++) distances[i] = -1;

    distances[start] = 0;
    visited[start] = VISITED;
    enqueue(queue, start);

    while(!empty(queue)) {
        int front = dequeue(queue);
        for(int current_vertex = 1; current_vertex<=my_graph.vertexes_number; current_vertex++) {
            if(my_graph.matrix[front][current_vertex] == 1) {
                if(visited[current_vertex] == NOT_VISITED) {
                    visited[current_vertex] = VISITED;
                    enqueue(queue, current_vertex);
                    distances[current_vertex] = distances[front] + 1;
                } else continue;
            }
        }
    }

    actual_distance = distances[stop];

    dealloc_queue(queue); queue = NULL;
    free(visited);        visited = NULL;
    free(distances);      distances = NULL;
    return actual_distance;
}

char* display_distance(char* text, int distance) {
    char* string_number = (char*)calloc(3, sizeof(char));
    strcpy(text, "Distanta dintre nodul de pornire si nodul de plecare este: ");
    sprintf(string_number, "%d", distance);
    strcat(text,  string_number);
    strcat(text, ".");

    free(string_number); string_number = NULL;
    return text;
}

void dealloc_graph(GRAPH* my_graph) {
    for(int i = 0; i<=my_graph->vertexes_number; i++) {
        free(my_graph->matrix[i]); my_graph->matrix[i] = NULL;
    }

    free(my_graph); my_graph = NULL;
}