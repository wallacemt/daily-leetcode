int** pacificAtlantic(int** heights, int heightsSize, int* heightsColSize, int* returnSize, int** returnColumnSizes) {
    if (!heights || heightsSize == 0 || !heightsColSize || heightsColSize[0] == 0) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }
    int rows = heightsSize;
    int cols = heightsColSize[0];
    int** pacific = (int**)malloc(rows * sizeof(int*));
    int** atlantic = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        pacific[i] = (int*)calloc(cols, sizeof(int));
        atlantic[i] = (int*)calloc(cols, sizeof(int));
    }
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    void dfs(int r, int c, int** ocean) {
        ocean[r][c] = 1;
        for (int d = 0; d < 4; d++) {
            int new_r = r + directions[d][0];
            int new_c = c + directions[d][1];
            if (new_r >= 0 && new_r < rows && new_c >= 0 && new_c < cols &&
                !ocean[new_r][new_c] && heights[new_r][new_c] >= heights[r][c]) {
                dfs(new_r, new_c, ocean);
            }
        }
    }
    for (int c = 0; c < cols; c++) {
        dfs(0, c, pacific);
        dfs(rows - 1, c, atlantic);
    }
    for (int r = 0; r < rows; r++) {
        dfs(r, 0, pacific);
        dfs(r, cols - 1, atlantic);
    }
    int** result = (int**)malloc(rows * cols * sizeof(int*));
    *returnColumnSizes = (int*)malloc(rows * cols * sizeof(int));
    int count = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (pacific[r][c] && atlantic[r][c]) {
                result[count] = (int*)malloc(2 * sizeof(int));
                result[count][0] = r;
                result[count][1] = c;
                (*returnColumnSizes)[count] = 2;
                count++;
            }
        }
    }
    *returnSize = count;
    return result;
}