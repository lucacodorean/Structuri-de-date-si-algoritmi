#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUME 15

typedef struct{
    char nume[MAX_NUME], prenume[MAX_NUME];
    unsigned short int varsta, note[3];
    float medie;
} STUDENT;


void init_list(STUDENT*, int, FILE*);
void print_list(STUDENT*, int);
void calculate_avg(STUDENT*, int);
void increment_grades(STUDENT*, int);

int main(void) {
    FILE* f = fopen("data.in", "r");
    
    int size; 
    fscanf(f, "%d", &size);
    STUDENT* studenti = (STUDENT*)calloc(size, sizeof(STUDENT));
    init_list(studenti, size, f);

    printf("\nINAINTE DE INCREMENTARE:\n");
    calculate_avg(studenti, size);
    print_list(studenti, size);

    printf("\nDUPA INCREMENTARE:\n");
    increment_grades(studenti,size);
    calculate_avg(studenti, size);
    print_list(studenti, size);

    free(studenti); studenti = NULL;
    return 0;
}


void init_list(STUDENT* arr, int size, FILE* f) {
    for(int i = 0; i<size; i++) 
        fscanf(f, "%s %s %d %d %d %d", arr[i].nume, arr[i].prenume, &arr[i].varsta, &arr[i].note[0], &arr[i].note[1], &arr[i].note[2]);
    fclose(f);
}

void print_list(STUDENT* arr, int size) {
    for(int i = 0; i<size; i++) printf("%s %s %d %d %d %d\n\tMedia: %.2f\n", arr[i].nume, arr[i].prenume, arr[i].varsta, arr[i].note[0], arr[i].note[1], arr[i].note[2], arr[i].medie);
}

void increment_grades(STUDENT* arr, int size) {
    for(int i = 0; i<size; i++) {
        for(int j = 0; j<size; j++) {
            arr[i].note[j] += (arr[i].note[j] < 10 ? 1 : 0);
        }
    }
}

void calculate_avg(STUDENT* arr, int size) {
    for(int i = 0; i<size; i++) arr[i].medie = (arr[i].note[0] + arr[i].note[1] + arr[i].note[2])/ 3.0;
}
