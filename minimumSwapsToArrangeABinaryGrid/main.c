int minSwaps(int** grid, int gridSize, int* gridColSize) {
    int* matrix = (int*)malloc(gridSize * sizeof(int));
    if (!matrix) 
        return -1;

    int n = gridSize - 1;

    for (int r = 0; r < gridSize; r++) {
        int i;
        for (i = n; i >= 0; i--) {
            if (grid[r][i] == 1) 
                break;
        }
        matrix[r] = n - i;
    }

    int swap = 0;
    int mSize = gridSize;

    while (mSize > 0) {
        int i, row = 0;
        for (i = 0; i < mSize; i++) {
            row = matrix[i];
            if (row >= n) 
                break;
        }
        if (row < n) {
            free(matrix);
            return -1;
        }

        swap += i;
        for (int j = i; j < mSize - 1; j++) {
            matrix[j] = matrix[j + 1];
        }
        mSize--;
        n--;
    }

    free(matrix);
    return swap;
}