int cmpDesc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int largestSubmatrix(int** matrix, int matrixSize, int* matrixColSize) {
    if (matrixSize == 0) 
        return 0;

    int m = matrixSize;
    int n = matrixColSize[0];
    int maxArea = 0;

    int* heights = (int*)calloc(n, sizeof(int));
    if (!heights) return 0;

    for (int i = 0; i < m; i++) {
        // Atualizar alturas
        for (int j = 0; j < n; j++) {
            heights[j] = matrix[i][j] ? heights[j] + 1 : 0;
        }

        int maxHeight = 0;
        for (int j = 0; j < n; j++) {
            if (heights[j] > maxHeight) maxHeight = heights[j];
        }
        
        if (maxHeight * n <= maxArea) continue;

        int* sortedH = (int*)malloc(n * sizeof(int));
        if (!sortedH) {
            free(heights);
            return maxArea;
        }

        memcpy(sortedH, heights, n * sizeof(int));
        qsort(sortedH, n, sizeof(int), cmpDesc);

        for (int j = 0; j < n; j++) {
            int area = sortedH[j] * (j + 1);
            if (area > maxArea) {
                maxArea = area;
            } else if (sortedH[j] == 0) {
                break; // Sem mais alturas válidas
            }
        }

        free(sortedH);
    }

    free(heights);
    return maxArea;
}