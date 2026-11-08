#include <stdlib.h>

/**
 * Conta servidores que podem se comunicar (mesma linha ou coluna).
 * Complexidade de Tempo: O(m * n)
 * Complexidade de Espaço: O(m + n)
 */
int countServers(int** grid, int gridSize, int* gridColSize) {
    if (gridSize <= 0 || gridColSize[0] <= 0) return 0;

    int m = gridSize;
    int n = gridColSize[0];

    // Alocação dinâmica para evitar estouro de pilha em grades grandes
    int* rowCount = (int*)calloc(m, sizeof(int));
    int* colCount = (int*)calloc(n, sizeof(int));

    if (!rowCount || !colCount) {
        free(rowCount);
        free(colCount);
        return 0;
    }

    // Primeiro passo: Contar quantos servidores existem em cada linha e coluna
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                rowCount[i]++;
                colCount[j]++;
            }
        }
    }

    int totalCommunicatingServers = 0;

     for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                if (rowCount[i] > 1 || colCount[j] > 1) {
                    totalCommunicatingServers++;
                }
            }
        }
    }

    free(rowCount);
    free(colCount);

    return totalCommunicatingServers;
}
