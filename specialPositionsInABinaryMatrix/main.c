int numSpecial(int** mat, int matSize, int* matColSize) {
    int m = matSize;
    int n = matColSize[0];
    
    int* rowSum = (int*)malloc(m * sizeof(int));
    int* colSum = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < m; i++) rowSum[i] = 0;
    for (int j = 0; j < n; j++) colSum[j] = 0;
    
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            rowSum[r] += mat[r][c];
            colSum[c] += mat[r][c];
        }
    }
    
    int special = 0;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (mat[r][c] == 1 && rowSum[r] == 1 && colSum[c] == 1) {
                special++;
            }
        }
    }
    
    // Liberar memória
    free(rowSum);
    free(colSum);
    
    return special;
}