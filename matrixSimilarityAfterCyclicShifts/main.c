bool areSimilar(int** mat, int matSize, int* matColSize, int k) {
    int rows = matSize;
    int cols = *matColSize;
    k %= cols;

    if (k == 0) {
        return true; 
    }
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Compara mat[i][j] com mat[i][(j + k) % cols]
            if (mat[i][j] != mat[i][(j + k) % cols]) {
                return false; 
            }
        }
    }
    
    return true;
}