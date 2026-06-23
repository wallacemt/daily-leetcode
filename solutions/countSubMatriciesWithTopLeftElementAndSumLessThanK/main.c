int countSubmatrices(int** grid, int gridSize, int* gridColSize, int k) {
    int r = gridSize;
    int c = gridColSize[0];

    long long* cols = calloc(c, sizeof(long long));
    int res = 0;

    for (int i = 0; i < r; i++) {
        long long row_sum = 0;
        for (int j = 0; j < c; j++) {
            cols[j] += grid[i][j];
            row_sum += cols[j];
            if (row_sum <= k)
                res++;
        }
    }

    free(cols);
    return res;}