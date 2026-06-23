#include <stdlib.h>
int** rotateGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize;
    int n = gridColSize[0];
    int layers = (m < n ? m : n) >> 1;  // Divisão por 2 mais rápida

    for (int layer = 0; layer < layers; layer++) {
        int top = layer, left = layer;
        int bottom = m - 1 - layer, right = n - 1 - layer;

        // Cálculo otimizado do número de elementos
        int height = bottom - top;
        int width = right - left;
        int numElements = (height + width) << 1;  // 2 * (height + width)

        // Pré-calcular o shift
        int shift = k % numElements;
        if (shift == 0) continue;  // Pular se não há rotação

        int* temp = (int*)malloc(numElements * sizeof(int));
        int idx = 0;

        // Extrair elementos
        for (int j = left; j < right; j++) 
            temp[idx++] = grid[top][j];
        for (int i = top; i < bottom; i++) 
            temp[idx++] = grid[i][right];
        for (int j = right; j > left; j--) 
            temp[idx++] = grid[bottom][j];
        for (int i = bottom; i > top; i--) 
            temp[idx++] = grid[i][left];

        // Recolocar elementos com shift
        idx = 0;
        int shiftedIdx;
        for (int j = left; j < right; j++) {
            shiftedIdx = (idx + shift) % numElements;
            grid[top][j] = temp[shiftedIdx];
            idx++;
        }
        for (int i = top; i < bottom; i++) {
            shiftedIdx = (idx + shift) % numElements;
            grid[i][right] = temp[shiftedIdx];
            idx++;
        }
        for (int j = right; j > left; j--) {
            shiftedIdx = (idx + shift) % numElements;
            grid[bottom][j] = temp[shiftedIdx];
            idx++;
        }
        for (int i = bottom; i > top; i--) {
            shiftedIdx = (idx + shift) % numElements;
            grid[i][left] = temp[shiftedIdx];
            idx++;
        }

        free(temp);
    }

    // Set return metadata
    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) 
        (*returnColumnSizes)[i] = n;

    return grid;
}