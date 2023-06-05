#include <stdio.h>
#include <stdlib.h>

#define INF -1

void cut(int* profits, int len, int r[100], int s[100]) {
    for(int i = 0; i<=len; i++) {
        r[i] = s[i] = 0;
    }

    for(int i = 1; i<=len; i++) {
        int result_act = INF;

        for(int j = 1; j<=i; j++) {
            if(result_act < profits[j] + r[i-j]) {
                result_act = profits[j] + r[i-j];
                s[i] = j;
            }
        }

        r[i] = result_act;

        printf("\n\n\tIteratia %d:\n", i);
        for(int i = 0; i<=len; i++) printf("%d ", r[i]);
        printf("\n");
        for(int j = 0; j<=len; j++) printf("%d ", s[j]);
    }
}

void print_solution(int n, int* profits) {
    int* r = (int*)calloc(n,sizeof(int));
    int* s = (int*)calloc(n,sizeof(int));
    cut(profits, n, r, s);

    printf("\nProfit optim: %d\n", r[n]);

    while(n>0) {
        printf("%d ", s[n]);
        n-=s[n];
    }

    free(r);
    free(s);
}

int main(void) {
    int profits[11] = {0,1,8,5,10,9,17,11,20,25,30};
    int n = 10;
   
    print_solution(n,profits);
    return 0;
}