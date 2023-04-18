/**
 * @file lab2.2.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief 
 * @version 0.1
 * @date 2023-02-28
 * 
 * @copyright Copyright (c) 2023

Se citesc de la tastatura 2 numere, CAPACITY elemente reale. Sa se scrie o functie care adauga un element in sir,
pe ultima pozitie a sirului. Folosind functia creata sa se insereze in sir SIZE numere. Ce se intampla daca
CAPACITY ≥ SIZE si daca CAPACITY < SIZE. Afisati sirul de numere dupa fiecare operatie de inserare.
**/

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    unsigned short int capacity, nr_elem;
    float* data;
} LIST;

void afisare(LIST);
void init_list(LIST*);
void insert_last(LIST*, float);
void insert_first(LIST*, float);

int main(void) {
    LIST arr;
    init_list(&arr);

    for(int i = 1; i<=5; i++) insert_first(&arr, i);
    afisare(arr);
    return 0;
}

void init_list(LIST* arr) {
    arr->capacity = 5;
    arr->nr_elem = 0;
    arr->data = (float*)calloc(arr->capacity, sizeof(float));
}

void afisare(LIST arr) {
    for(int i = 0; i<arr.nr_elem; i++) printf("%.2f ", arr.data[i]);
}

void insert_last(LIST* s, float value) {
    if(s->capacity == s->nr_elem) {
        s->capacity *= 2;
        s->data = (float*)realloc(s->data, s->capacity * sizeof(float));
    } 
    s->data[s->nr_elem++] = value;
}

void insert_first(LIST* s, float value) {
    if(s->capacity == s->nr_elem) {
        s->capacity *= 2;
        s->data = (float*)realloc(s->data, s->capacity * sizeof(float));
    } 
    
    s->nr_elem++;
    for(int i = s->nr_elem; i>=0; i--) s->data[i] = s->data[i-1];
    s->data[0] = value;
}