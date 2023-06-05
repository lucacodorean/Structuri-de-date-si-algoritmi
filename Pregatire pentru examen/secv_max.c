#include <stdio.h>
#include <stdlib.h>

int max(int, int);
void kadane(FILE*, int, int*, int*, int*);

int main(void) {
    FILE* data_in = fopen("numbers.in", "r");

    if(data_in == NULL) {
        return -1;
    }    

    int size = 0;
    fscanf(data_in, "%d", &size);
    
    int start = 0, stop = 0, s_max;
    kadane(data_in, size, &start, &stop, &s_max);
    printf("Suma maxima este %d si este delimtiata de indecsii %d %d.", s_max, start, stop);
    return 0;
}

int max(int a, int b) { return a<b ? b : a; }

void kadane(FILE* path, int size, int* return_start, int* return_stop, int* suma) {

    int* values = (int*)calloc(size,sizeof(int));
    int* dp = (int*)calloc(size,sizeof(int));

    int result, start = 0, stop = 0;
    for(int i = 0; i<size; i++) fscanf(path, "%d", &values[i]);

    dp[0] = values[0];

    for(int i = 1; i<size; i++) {
        if(values[i] + dp[i-1] > dp[i]) {
            start = i;
        }

        dp[i]  = max(values[i], dp[i-1] + values[i]);
        result = max(result, dp[i]);
    }

    free(dp);

    start--;
    stop = start;
    int aux = result;
    while(aux>0) {
        aux -= values[start];
        start--;
    }

    free(values); 

    (*return_start) = start + 1;
    (*return_stop)  = stop;
    (*suma)         = result;
}