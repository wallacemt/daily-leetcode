 
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    int value;
    int originalIndex;
} Pair;

int comparePairs(const void *a, const void *b) {
    return (((Pair *)a)->value - ((Pair *)b)->value);
}

int* arrayRankTransform(int* arr, int arrSize, int* returnSize) {
    *returnSize = arrSize;

    if (arrSize == 0)
        return (int*)malloc(0); 
    Pair *pairs = (Pair *)malloc(arrSize * sizeof(Pair));
    for (int i = 0; i < arrSize; i++) {
        pairs[i].value = arr[i];
        pairs[i].originalIndex = i;
    }
 
    qsort(pairs, arrSize, sizeof(Pair), comparePairs);
 
    int *result = (int *)malloc(arrSize * sizeof(int));
 
    int rank = 0;
    int lastValue = INT_MIN;

    for (int i = 0; i < arrSize; i++) {
        if (pairs[i].value != lastValue) {
            rank++;
            lastValue = pairs[i].value;
        } 
        result[pairs[i].originalIndex] = rank;
    }

    free(pairs);
    return result;
}