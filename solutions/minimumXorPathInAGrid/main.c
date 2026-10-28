#define MAX_XOR 1024
int minCost(int** grid, int gridSize, int* gridColSize) {
int m = gridSize;
int n = gridColSize[0];
unsigned char (*dp)[MAX_XOR] = calloc(n, sizeof(*dp));

dp[0][grid[0][0]] = 1;

for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
        if (i == 0 && j == 0) {
            continue;
        }

        unsigned char next[MAX_XOR] = {0};
        int value = grid[i][j];

        for (int k = 0; k < MAX_XOR; k++) {
            if (dp[j][k] || (j > 0 && dp[j - 1][k])) {
                next[k ^ value] = 1;
            }
        }

        memcpy(dp[j], next, sizeof(next));
    }
}

int answer = -1;

for (int k = 0; k < MAX_XOR; k++) {
    if (dp[n - 1][k]) {
        answer = k;
        break;
    }
}

free(dp);
return answer;

}