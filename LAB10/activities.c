/**
 * @file activities.c
 * @author Luca-Andrei Codorean (codorean.do.luca@student.utcluj.ro)
 * @brief 
 * @version 0.1
 * @date 2023-05-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    char* activity_name;
    int start_time, end_time;
} ACTIVITY;

void sort(ACTIVITY*, int);
void swap(ACTIVITY*, ACTIVITY*);
void init_activities(ACTIVITY*, FILE*, int);
int  greedy(ACTIVITY*, int);

int main(void) {

    FILE* data_in = fopen("data.in", "r");

    if(data_in == NULL) {
        printf("Eroare la deschiderea fisierelor I/O.");
        return -1;
    }

    int size; 
    fscanf(data_in, "%d", &size);

    ACTIVITY* activities_arr = (ACTIVITY*)calloc(size, sizeof(ACTIVITY));
    init_activities(activities_arr, data_in, size); fclose(data_in);

    sort(activities_arr, size);
    int ok = greedy(activities_arr, size); 

    printf("\nAu fost selectate %d activitati.", ok);
   
    for(int i = 0; i<size; i++) free(activities_arr[i].activity_name);
    free(activities_arr);

    printf("\nCompiled in %0.3f seconds.", clock()*1.0/CLOCKS_PER_SEC);
    return 0;
}

void init_activities(ACTIVITY* arr, FILE* path, int size) {

    for(int i = 0; i<size; i++) arr[i].activity_name = (char*)calloc(30,sizeof(char));

    for(int i = 0; i<size; i++) {
        fscanf(path, "%s %d %d", arr[i].activity_name, &arr[i].start_time, &arr[i].end_time);
    }
}

void swap(ACTIVITY* first, ACTIVITY* second) {
     ACTIVITY aux = *first;
     *first = *second;
     *second = aux;
}

void sort(ACTIVITY* arr, int size) {
    for(int i = 0; i<size; i++) {
        for(int j = i+1; j<size; j++) {
            if(arr[i].end_time > arr[j].end_time) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

int greedy(ACTIVITY* arr, int size) {

    int contor = 1;

    ACTIVITY current_activity = arr[0];
    printf("Activitate selectata: %s \t de la %d la %d", current_activity.activity_name, current_activity.start_time, current_activity.end_time);
    
    for(int i = 0; i<size; i++) {
        if(arr[i].start_time >= current_activity.end_time) {
            printf("\nActivitate selectata: %s \t de la %d la %d", arr[i].activity_name, arr[i].start_time, arr[i].end_time);
            contor++;
            current_activity = arr[i];
        }
    }

    return contor;
}

