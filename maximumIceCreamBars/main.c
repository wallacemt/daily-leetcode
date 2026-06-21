#include <stdlib.h>
#include <string.h>

 
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int maxIceCream(int* costs, int costsSize, int coins) {
    
    qsort(costs, costsSize, sizeof(int), compare);
    
    int res = 0;
     
    for (int i = 0; i < costsSize; i++) {
        if (costs[i] <= coins) {
            coins -= costs[i];
            res++;
        } else {
            break;  
        }
    }
    
    return res;
}