#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxDepthAfterSplit(char* seq, int* returnSize) {
    int len = strlen(seq);
    *returnSize = len;
    
    int* result = (int*)malloc(len * sizeof(int));
    if (!result) return NULL;

    for (int i = 0; i < len; ++i) { 
        result[i] = ((seq[i] & 1) ^ (i & 1));
    }

    return result;
}