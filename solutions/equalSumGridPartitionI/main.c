#include <stdbool.h>
#include <stdlib.h>

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    
    long long totalSum = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            totalSum += grid[i][j];
        }
    }
    
    if (totalSum & 1) return false;
    
    long long targetSum = totalSum >> 1;  // Divisão por 2 mais rápida
    long long currentSum = 0;
    
    for (int j = 0; j < cols - 1; j++) {
        for (int i = 0; i < rows; i++) {
            currentSum += grid[i][j];
        }
        if (currentSum == targetSum) return true;
    }
    
    currentSum = 0;
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < cols; j++) {
            currentSum += grid[i][j];
        }
        if (currentSum == targetSum) return true;
    }
    
    return false;
}