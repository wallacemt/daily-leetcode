#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int DIRS[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
int max(int a, int b) {
    return (a > b) ? a : b;
}

int dfs(int i, int j, int dir, int canTurn, int target, int** grid, int rows, int cols, int*** memo) {
   
    i += DIRS[dir][0];
    j += DIRS[dir][1];
    
    if (i < 0 || i >= rows || j < 0 || j >= cols || grid[i][j] != target) {
        return 0;
    }
    
    int state = (dir << 1) | canTurn;
    if (memo[i][j][state] != 0) {
        return memo[i][j][state];
    }
    
    int res = dfs(i, j, dir, canTurn, 2 - target, grid, rows, cols, memo);
    
    if (canTurn == 1) {
        int nextDir = (dir + 1) % 4;
        res = max(res, dfs(i, j, nextDir, 0, 2 - target, grid, rows, cols, memo));
    }
    
    return memo[i][j][state] = res + 1;
}

int lenOfVDiagonal(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;           
    int n = gridColSize[0];     
    
    int*** memo = (int***)malloc(m * sizeof(int**));
    for (int i = 0; i < m; i++) {
        memo[i] = (int**)malloc(n * sizeof(int*));
        for (int j = 0; j < n; j++) {
            memo[i][j] = (int*)calloc(8, sizeof(int));
        }
    }
    
    int maxLen = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] != 1) {
                continue;
            }
            
            for (int k = 0; k < 4; k++) {
                maxLen = max(maxLen, dfs(i, j, k, 1, 2, grid, m, n, memo) + 1);
            }
        }
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            free(memo[i][j]);
        }
        free(memo[i]);
    }
    free(memo);
    
    return maxLen;
}
