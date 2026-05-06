char** rotateTheBox(char** boxGrid, int boxGridSize, int* boxGridColSize, int* returnSize, int** returnColumnSizes) {
    int row = boxGridSize;
    int col = boxGridColSize[0];
    char** rotate = (char**)malloc(col * sizeof(char*));
    *returnColumnSizes = (int*)malloc(col * sizeof(int));
    for (int i = 0; i < col; i++) {
        rotate[i] = (char*)malloc(row * sizeof(char));
        (*returnColumnSizes)[i] = row;
        for (int j = 0; j < row; j++) {
            rotate[i][j] = '.';
        }
    }
    for (int k = 0; k < row; k++) {
        int bottom = col - 1;
        for (int j = col - 1; j >= 0; j--) {
            if (boxGrid[k][j] == '#') {
                rotate[bottom][row - 1 - k] = '#';
                bottom--;
            } 
            else if (boxGrid[k][j] == '*') {
                rotate[j][row - 1 - k] = '*';
                bottom = j - 1;
            }
        }
    }
    *returnSize = col;
    return rotate;
}