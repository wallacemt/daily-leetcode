#include <stdbool.h>
#include <stdio.h>

bool dfs(int** grid, int m, int n, int r, int c) {
    if (r < 0 || r >= m || c < 0 || c >= n) {
        return false; // Se saímos dos limites, a ilha não é fechada
    }

    if (grid[r][c] == 1) {
        return true; // Se encontramos terra, continuamos a busca
    }

    grid[r][c] = 1;

    // Explorar todas as direções
    bool up = dfs(grid, m, n, r - 1, c);
    bool down = dfs(grid, m, n, r + 1, c);
    bool left = dfs(grid, m, n, r, c - 1);
    bool right = dfs(grid, m, n, r, c + 1);

    return up && down && left && right;
}

int closedIsland(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    int count = 0;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // Iniciar DFS se encontrarmos água (0)
            if (grid[i][j] == 0 && dfs(grid, m, n, i, j)) {
                count++; // Contar a ilha fechada
            }
        }
    }

    return count; // Retornar o número de ilhas fechadas
}
