bool isValid(int** grid, int i, int j, int k) {
    int sum = 0;

    for (int x = i; x < i + k; x++) {
        int s = 0;
        for (int y = j; y < j + k; y++) {
            s += grid[x][y];
        }
        if (x == i) {
            sum = s;
        } else if (sum != s) {
            return false;
        }
    }
    
    for (int y = j; y < j + k; y++) {
        int s = 0;
        for (int x = i; x < i + k; x++) {
            s += grid[x][y];
        }
        if (sum != s) {
            return false;
        }
    }
    
    int diag1 = 0;
    for (int d = 0; d < k; d++) {
        diag1 += grid[i + d][j + d];
    }
    if (sum != diag1) {
        return false;
    }
    int diag2 = 0;
    for (int d = 0; d < k; d++) {
        diag2 += grid[i + d][j + k - 1 - d];
    }
    
    return sum == diag2;
}

int largestMagicSquare(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int maxSize = (m < n) ? m : n;
    int res = 1;
    
    for (int k = maxSize; k >= 2; k--) {
        for (int i = 0; i + k <= m; i++) {
            for (int j = 0; j + k <= n; j++) {
                if (isValid(grid, i, j, k)) {
                    return k;  // Retornar imediatamente
                }
            }
        }
    }
    
    return res;
}