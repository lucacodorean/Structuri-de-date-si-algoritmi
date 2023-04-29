#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"

typedef struct _Graph {
    int vertexes, edges_number;
    int** adj;
} GRAPH;

#define NOT_VISITED 0
#define VISITED 1

GRAPH* init_graph(int);
void init_adj_graph(GRAPH*, FILE*);
int BFS(GRAPH, int, int*);
enum colors {WHITE = 0, GREY = 1, BLACK = 2};

int main(void) {
    FILE* data_in = fopen("data.in", "r");
    FILE* data_out = fopen("data.out", "w");

    if(data_in == NULL) {
        return 0;
    } 

    int size; fscanf(data_in, "%d", &size);
    GRAPH* my_graph = init_graph(size);
    init_adj_graph(my_graph, data_in);  fclose(data_in);

    int result;
    int* visited = (int*)calloc(my_graph->vertexes+1, sizeof(int));
    for(int i = 1; i<my_graph->vertexes; i++) {
        if(visited[i] == NOT_VISITED)
             result = BFS(*my_graph, i, visited);

        if(result == 1) break;
    }
   
    printf("Graful %s bipartit.", result == 0 ? "nu este" : "este");
    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

GRAPH* init_graph(int size) {
    GRAPH* new_graph = (GRAPH*)calloc(1,sizeof(GRAPH));

    new_graph->vertexes = size;
    new_graph->edges_number = 0;

    new_graph->adj = (int**)calloc(new_graph->vertexes+1, sizeof(int*));
     for(int i = 1; i<=size; i++) new_graph->adj[i] = (int*)calloc(new_graph->vertexes+1, sizeof(int));
    return new_graph;
}

void init_adj_graph(GRAPH* my_graph, FILE* path) {

    int x, y;
    while(fscanf(path, "%d %d", &x, &y)==2) {
        my_graph->edges_number++;
        my_graph->adj[x][y] = 1;
    }
}

int BFS(GRAPH my_graph, int start, int* visited) {
    QUEUE*  queue        = (QUEUE*)calloc(1,sizeof(QUEUE));                                 //  initializam coada
    int*    color        = (int*)calloc(my_graph.vertexes+1, sizeof(int));                  //  initializam un array unde tinem minte ordinea culorilor
    
    int l = 0;
    color[start] = GREY;          
    visited[start] = VISITED;                                                               //  marcam nodul de start in curs de prelucrare
    enqueue(queue, start);                                                                  //  il incaram in coada pentru a incepe algoritmul

    while(!empty(queue)) {                                                                  //  cat timp coada nu este vida
        int front = dequeue(queue);                                                         //  preluam elementul accesibil din coada
                                                                                            //  salvam nodurile parcurse
        for(int current_vertex = 1; current_vertex<=my_graph.vertexes; current_vertex++) {  //  parcurgem nodurile adiacente cu nodul salvat in front  
            if(my_graph.adj[front][current_vertex] == 1) {                                  
                if(color[current_vertex] == WHITE) {         
                    visited[current_vertex] = VISITED;
                    color[current_vertex] = (color[front] == GREY ? BLACK : GREY);          //  le atribuim o culoare in funtie de culoarea nodului din front
                    enqueue(queue, current_vertex);                                         //  le adaugam in coada pentru a le parcurgere ulterior                                        
                }   
                else if(color[front]==color[current_vertex]) {                              //  altfel, daca culorile pentru front si nodul curent coincid, inseamna ca graful nu poate sa fie bipartit
                    for(int i = 1; i<l; i++)                                                //  afisam istoricul nodurilor parcuse
                    printf("\n");
                    dealloc_queue(queue); queue = NULL;                                     //  eliberam spatiul de memorie alocat cozii.
                    free(color);          color = NULL;                                     //  eliberam spatiul de memorie alocat vectorului de colorare.        
                    return 0;                                                               //  marcam faptul ca graful nu este bipartit prin return 0
                }
            } 
        }
    }

    dealloc_queue(queue); queue = NULL;                                                     //  eliberam spatiul de memorie alocat cozii.
    free(color);          color = NULL;                                                     //  eliberam spatiul de memorie alocat vectorului de colorare.
    return 1;                                                                               //   daca nu am returnat 0, inseamna ca graful este bipartit, deci returnam 1
}