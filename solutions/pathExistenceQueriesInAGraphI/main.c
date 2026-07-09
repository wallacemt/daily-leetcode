#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool* pathExistenceQueries(int n, int* nums, int numsSize, int maxDiff,
                           int** queries, int queriesSize,
                           int* queriesColSize, int* returnSize) {

    *returnSize = queriesSize;
    bool* queryResult = (bool*)calloc(queriesSize, sizeof(bool));
    
    if (!queryResult) return NULL;

    int* distances = (int*)malloc(numsSize * sizeof(int));
    if (!distances) {
        free(queryResult);
        return NULL;
    }

    distances[0] = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] - nums[i - 1] <= maxDiff) {
            distances[i] = distances[i - 1] + 1;
        } else {
            distances[i] = 0;
        }
    }

     for (int i = 0; i < queriesSize; i++) {
        int u = queries[i][0];
        int v = queries[i][1];

        if (u < 0 || u >= numsSize || v < 0 || v >= numsSize) {
            queryResult[i] = false;
            continue;
        }

        int minIdx = (u < v) ? u : v;
        int maxIdx = (u > v) ? u : v;
        int indexDistance = maxIdx - minIdx;

        if (distances[maxIdx] >= indexDistance) {
            queryResult[i] = true;
        }
    }

    free(distances);
    return queryResult;
}