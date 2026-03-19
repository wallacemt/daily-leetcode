int numberOfSubmatrices(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];

    int* ox = (int*)calloc(n, sizeof(int));
    int* oy = (int*)calloc(n, sizeof(int));

    int res = 0;

    for (int i = 0; i < m; i++) {
        int rowX = 0, rowY = 0;

        for (int j = 0; j < n; j++) {
            char cell = grid[i][j];
            
            if (cell == 'X')
                rowX++;
            else if (cell == 'Y')
                rowY++;

            ox[j] += rowX;
            oy[j] += rowY;

            // Simplificado: se ox[j] == oy[j], então ox[j] > 0 é garantido
            if (ox[j] == oy[j] && ox[j] > 0)
                res++;
        }
    }

    free(ox);
    free(oy);
    return res;
}