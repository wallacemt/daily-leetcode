#include <stdio.h>
#include <stdbool.h>

static long long dfs(int** grid, int m, int n, int r, int c) { 
    long long sum = grid[r][c];
    grid[r][c] = 0; // Marca como visitada
 
    if (r > 0 && grid[r - 1][c] > 0) sum += dfs(grid, m, n, r - 1, c); // Cima
    if (r + 1 < m && grid[r + 1][c] > 0) sum += dfs(grid, m, n, r + 1, c); // Baixo
    if (c > 0 && grid[r][c - 1] > 0) sum += dfs(grid, m, n, r, c - 1); // Esquerda
    if (c + 1 < n && grid[r][c + 1] > 0) sum += dfs(grid, m, n, r, c + 1); // Direita

    return sum; // Retorna a soma total da ilha
}

int countIslands(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    int count = 0;
 
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Se encontramos uma célula positiva, iniciamos DFS
            if (grid[i][j] > 0) {
                long long islandSum = dfs(grid, m, n, i, j);
                // Verifica se a soma da ilha é divisível por k
                if (islandSum % k == 0) {
                    count++; // Contamos a ilha
                }
            }
        }
    }
    return count;  
}
 
