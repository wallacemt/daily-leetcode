#include <stdio.h>
#include <stdlib.h>

static int compareAsc(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

static int compareDesc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int** sortMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    *returnSize = n;
    *returnColumnSizes = malloc(n * sizeof(int));
    
    int** result = malloc(n * sizeof(int*));
    for(int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = n;
        result[i] = malloc(n * sizeof(int));
        for(int j = 0; j < n; j++) {
            result[i][j] = grid[i][j];
        }
    }
    
    for(int d = -(n-1); d <= (n-1); d++) {
        int diagonal[n];
        int count = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i - j == d) {
                    diagonal[count++] = result[i][j];
                }
            }
        }
        
        if(count == 0) continue;
        
        if(d >= 0) {
            qsort(diagonal, count, sizeof(int), compareDesc);
        } else {
            qsort(diagonal, count, sizeof(int), compareAsc);
        }
        
        int idx = 0;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(i - j == d) {
                    result[i][j] = diagonal[idx++];
                }
            }
        }
    }
    
    return result;
}
