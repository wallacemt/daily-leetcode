#include <stdlib.h>
#include <string.h>

void generateAllCombinations(char*** result, int* returnSize, int open, int close, int n, 
                             char* current, int idx, int* capacity) {
    if (open == n && close == n) {
        current[idx] = '\0';
        if (*returnSize >= *capacity) {
            *capacity <<= 1;
            *result = realloc(*result, sizeof(char*) * (*capacity));
        }
        (*result)[(*returnSize)++] = strdup(current);
        return;
    }

    if (open < n) {
        current[idx] = '(';
        generateAllCombinations(result, returnSize, open + 1, close, n, current, idx + 1, capacity);
    }
    
    if (close < open) {
        current[idx] = ')';
        generateAllCombinations(result, returnSize, open, close + 1, n, current, idx + 1, capacity);
    }
}

char** generateParenthesis(int n, int* returnSize) {
    // Catalan number: C(n) = (2n)! / ((n+1)! * n!)
    // Para n=10: ~16796 combinações
    int initialCapacity = 1 << (n + 4);
    
    char** result = malloc(sizeof(char*) * initialCapacity);
    char* current = malloc(2 * n + 1);
    
    *returnSize = 0;
    generateAllCombinations(&result, returnSize, 0, 0, n, current, 0, &initialCapacity);
    
    free(current);
    return result;
}