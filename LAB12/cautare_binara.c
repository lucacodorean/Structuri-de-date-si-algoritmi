#include <stdio.h>
#include <stdlib.h>

#define NOT_FOUND -1

int binary_search(int arr[], int left, int right, int el) {
    int mid = (left + right)/2;
    if(mid==left) {
        if(arr[mid] == el) return mid;
        return -1;
    }
    if(arr[mid] == el) return mid;
    else {
        if(arr[mid] < el) binary_search(arr, 0, mid, el);
        else binary_search(arr, mid, right, el);
    }

    return NOT_FOUND;
}

int bs(int arr[], int p, int q, int element) {
    while(1) {
        if(p >= q) {
            if(p==q) {
                if(arr[p]==element) return p;
            }
            return NOT_FOUND;
        }

        int middle = (p+q)/2;
        if(arr[middle] == element) {
            return middle;
        } 

        else if(arr[middle] > element) q = middle-1;
        else p = middle+1;
    }
    return NOT_FOUND;
}

int main(void) {
    int a[] = {-3,1,3,6,7,8,13,15};
    int n   = sizeof(a)/sizeof(int);
    int k   = -3;
    int p = 0, q = n;

    for(int i = -5; i<=18; i++) {
         printf("Valoarea %d \t%s a fost gasita.\n", i, bs(a,p,q,i) != -1 ? "" : " nu");
    }
    return 0;
}