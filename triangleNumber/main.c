int minimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    if (triangle == NULL || triangleSize == 0 || triangleColSize == NULL) {
        return 0;
    }

    for (int i = triangleSize - 2; i >= 0; i--) {
        for (int j = 0; j < triangleColSize[i]; j++) {
            int min = INT_MAX;
            for (int k = 0; k < 2; k++) {
                int nextCol = j + k;
                if (nextCol >= 0 && nextCol < triangleColSize[i + 1]) {
                    min = fmin(min, triangle[i + 1][nextCol]);
                }
            }
            triangle[i][j] += min;
        }
    }

    return triangle[0][0];
}

