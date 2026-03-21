int** reverseSubmatrix(int** grid, int gridSize, int* gridColSize, 
                       int x, int y, int k, int* returnSize, 
                       int** returnColumnSizes) {
    int rows = gridSize;
    int cols = gridColSize[0];
    
    // Alocação eficiente: matriz contígua
    int** res = (int**)malloc(rows * sizeof(int*));
    int* data = (int*)malloc(rows * cols * sizeof(int));
    
    for (int i = 0; i < rows; i++) {
        res[i] = data + i * cols;
    }
    
    *returnColumnSizes = (int*)malloc(rows * sizeof(int));
    *returnSize = rows;
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            res[i][j] = grid[i][j];
        }
        (*returnColumnSizes)[i] = cols;
    }
    
    int l = x;
    int r = x + k - 1;
    
    while (l < r) {  // Otimização: l < r em vez de l <= r
        for (int i = y; i < y + k; i++) {
            int temp = res[l][i];
            res[l][i] = res[r][i];
            res[r][i] = temp;
        }
        l++;
        r--;
    }
    
    return res;
}