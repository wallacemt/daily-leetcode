int uniquePaths(int** grid, int gridSize, int* gridColSize) {
    const long long MOD = 1000000007LL;
    int m = gridSize;
    int n = gridColSize[0];

    long long (*f)[2] = calloc(n, sizeof(*f));
    f[0][0] = 1;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i > 0) {
                if (grid[i - 1][j] == 0) {
                    f[j][0] = (f[j][0] + f[j][1]) % MOD;
                } else {
                    f[j][0] = f[j][1];
                }
            }

            if (j > 0) {
                if (grid[i][j - 1] == 0) {
                    f[j][1] = (f[j - 1][0] + f[j - 1][1]) % MOD;
                } else {
                    f[j][1] = f[j - 1][0];
                }
            }
        }
    }

    int ans = (int)((f[n - 1][0] + f[n - 1][1]) % MOD);

    free(f);
    return ans;
}