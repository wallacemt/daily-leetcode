#include <stdbool.h>

bool findRotation(int** mat, int matSize, int* matColSize, int** target, int targetSize, int* targetColSize) {
    int n = matSize;
    bool c0 = true, c90 = true, c180 = true, c270 = true;
    
    for (int i = 0; i < n && (c0 || c90 || c180 || c270); ++i) {
        for (int j = 0; j < n && (c0 || c90 || c180 || c270); ++j) {
            if (c0 && mat[i][j] != target[i][j]) {
                c0 = false;
            }
            if (c90 && mat[i][j] != target[j][n - 1 - i]) {
                c90 = false;
            }
            if (c180 && mat[i][j] != target[n - 1 - i][n - 1 - j]) {
                c180 = false;
            }
            if (c270 && mat[i][j] != target[n - 1 - j][i]) {
                c270 = false;
            }
        }
    }
    
    return c0 || c90 || c180 || c270;
}