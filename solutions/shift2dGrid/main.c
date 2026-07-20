/**
 * Versão corrigida e otimizada
 * Shift rotacional correto: cada elemento se move k posições
 */
int** shiftGrid(int** grid, int gridSize, int* gridColSize, int k, 
                int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int m = gridColSize[0];
    int total = n * m;
     
    k = k % total;
    
    int** res = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        res[i] = (int*)malloc(m * sizeof(int));
        (*returnColumnSizes)[i] = m;
    }
     
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) { 
            int src_idx = i * m + j;
             
            int dst_idx = (src_idx + k) % total;
             
            int dst_i = dst_idx / m;
            int dst_j = dst_idx % m; 
            res[dst_i][dst_j] = grid[i][j];
        }
    }
    
    *returnSize = n;
    return res;
}