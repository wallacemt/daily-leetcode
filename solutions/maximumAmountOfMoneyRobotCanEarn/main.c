#include <stdlib.h>
#include <limits.h>

int maximumAmount(int** coins, int coinsSize, int* coinsColSize) {
    int m = coinsSize;
    int n = coinsColSize[0];
    int MIN_VAL = INT_MIN / 2;

    int (*dfs)[3] = malloc((n + 1) * sizeof(*dfs));
    
    for (int j = 0; j <= n; j++) {
        dfs[j][0] = MIN_VAL;
        dfs[j][1] = MIN_VAL;
        dfs[j][2] = MIN_VAL;
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                dfs[1][0] = coins[i][j];
                dfs[1][1] = fmax(coins[i][j], 0);
                dfs[1][2] = fmax(coins[i][j], 0);
            } else {
                int prev_0 = fmax(dfs[j + 1][0], dfs[j][0]);
                int prev_1 = fmax(dfs[j + 1][1], dfs[j][1]);
                int prev_2 = fmax(dfs[j + 1][2], dfs[j][2]);

                dfs[j + 1][2] = fmax(coins[i][j] + prev_2, prev_1);
                dfs[j + 1][1] = fmax(coins[i][j] + prev_1, prev_0);
                dfs[j + 1][0] = coins[i][j] + prev_0;
            }
        }
    }

    int res = fmax(dfs[n][0], fmax(dfs[n][1], dfs[n][2]));
    
    free(dfs);
    return res;
}