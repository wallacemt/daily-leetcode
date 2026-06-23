#include <stdlib.h>
#include <string.h>

int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, 
                             int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int m = gridColSize[0];
    const int MOD = 12345;

    int** res = (int**)malloc(n * sizeof(int*));
    int* data = (int*)malloc(n * m * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        res[i] = data + i * m;
    }

    *returnSize = n;
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        (*returnColumnSizes)[i] = m;
    }

    long long pref = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            res[i][j] = (int)pref;
            pref = (pref * (grid[i][j] % MOD)) % MOD;
        }
    }

    long long suff = 1;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = m - 1; j >= 0; j--) {
            res[i][j] = (int)((long long)res[i][j] * suff % MOD);
            suff = (suff * (grid[i][j] % MOD)) % MOD;
        }
    }

    return res;
}