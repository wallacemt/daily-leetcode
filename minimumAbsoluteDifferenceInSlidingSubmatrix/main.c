#include <stdlib.h>
#include <limits.h>
#include <string.h>

int cmp(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int** minAbsDiff(int** grid, int gridSize, int* gridColSize, int k, 
                 int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = gridColSize[0];
    
    int out_m = m - k + 1;
    int out_n = n - k + 1;
    
    *returnSize = out_m;
    *returnColumnSizes = (int*)malloc(out_m * sizeof(int));
    int** ans = (int**)malloc(out_m * sizeof(int*));
    
    // Aloca uma única vez
    int* tmp = (int*)malloc(k * k * sizeof(int));
    
    for (int i = 0; i < out_m; ++i) {
        (*returnColumnSizes)[i] = out_n;
        ans[i] = (int*)malloc(out_n * sizeof(int));
        
        for (int j = 0; j < out_n; ++j) {
            // Extrai sub-matriz k×k
            int idx = 0;
            for (int x = 0; x < k; ++x) {
                for (int y = 0; y < k; ++y) {
                    tmp[idx++] = grid[i + x][j + y];
                }
            }
            
            // Ordena
            qsort(tmp, k * k, sizeof(int), cmp);
    
            int minDiff = INT_MAX;
            int distinctCount = 1;
            
            for (int p = 1; p < k * k; ++p) {
                if (tmp[p] != tmp[p - 1]) {
                    distinctCount++;
                    int diff = tmp[p] - tmp[p - 1];
                    minDiff = (diff < minDiff) ? diff : minDiff;
                    
                    // OTIMIZAÇÃO: Se encontrou diferença 1, é o mínimo possível
                    if (minDiff == 1) break;
                }
            }
            ans[i][j] = (distinctCount == 1) ? 0 : minDiff;
        }
    }
    
    free(tmp);
    return ans;
}