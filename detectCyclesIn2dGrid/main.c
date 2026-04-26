int find(int x, int* parent) {
    if (parent[x] != x) {
        parent[x] = find(parent[x], parent); // Compressão total
    }
    return parent[x];
}

bool union_sets(int a, int b, int* parent) {
    int ra = find(a, parent);
    int rb = find(b, parent);
    
    if (ra == rb) return true;  
    parent[ra] = rb;
    return false;
}

bool containsCycle(char** grid, int gridSize, int* gridColSize) {
    int rows = gridSize, cols = gridColSize[0];
    int* parent = (int*)malloc(rows * cols * sizeof(int));
    
    // Inicialização
    for (int i = 0; i < rows * cols; i++) {
        parent[i] = i;
    }
    
    // Verificação de adjacências
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int idx = i * cols + j;
            char cell = grid[i][j];
            
            if (j + 1 < cols && grid[i][j + 1] == cell) {
                if (union_sets(idx, idx + 1, parent)) {
                    free(parent);
                    return true;
                }
            }
            
            // Baixo
            if (i + 1 < rows && grid[i + 1][j] == cell) {
                if (union_sets(idx, idx + cols, parent)) {
                    free(parent);
                    return true;
                }
            }
        }
    }
    
    free(parent);
    return false;
}