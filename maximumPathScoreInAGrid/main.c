int maxPathScore(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    int k_limit = k + 1;
    int* dp = (int*)malloc(n * k_limit * sizeof(int));
    for (int i = 0; i < n * k_limit; i++) 
        dp[i] = -1;

    dp[k] = 0;

    int* combined = (int*)malloc(k_limit * sizeof(int));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            int curr = grid[i][j];

            for (int rk = 0; rk <= k; rk++) {
                combined[rk] = dp[j * k_limit + rk];
            }
            if (j > 0) {
                for (int rk = 0; rk <= k; rk++) {
                    combined[rk] = MAX(combined[rk], dp[(j - 1) * k_limit + rk]);
                }
            }

            if (curr != 0) {
                for (int rk = 0; rk <= k; rk++) 
                    dp[j * k_limit + rk] = -1;
                for (int rk = 1; rk <= k; rk++) {
                    if (combined[rk] != -1) {
                        dp[j * k_limit + rk - 1] = combined[rk] + curr;
                    }
                }
            } else {
                for (int rk = 0; rk <= k; rk++) {
                    dp[j * k_limit + rk] = combined[rk];
                }
            }
        }
    }

    int max_val = -1;
    for (int rk = 0; rk <= k; rk++) {
        max_val = MAX(max_val, dp[(n - 1) * k_limit + rk]);
    }

    free(dp);
    free(combined);
    return max_val;
}