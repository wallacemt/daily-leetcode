void rotate(int** matrix, int matrixSize, int* matrixColSize) {

    for (int i = 0; i < matrixSize; i++) {
        for (int j = i + 1; j < matrixSize; j++) {
            matrix[i][j] ^= matrix[j][i];
            matrix[j][i] ^= matrix[i][j];
            matrix[i][j] ^= matrix[j][i];
        }
    }

    int half = matrixSize >> 1;  
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < half; j++) {
            int right = matrixSize - 1 - j;
            // Swap inline
            matrix[i][j] ^= matrix[i][right];
            matrix[i][right] ^= matrix[i][j];
            matrix[i][j] ^= matrix[i][right];
        }
    }
}