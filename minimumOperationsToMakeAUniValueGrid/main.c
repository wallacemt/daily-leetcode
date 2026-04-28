
int cmp(const void* a, const void* b) {
    int diff = *(int*)a - *(int*)b;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}

int minOperations(int** grid, int gridSize, int* gridColSize, int x) {
    int total = gridSize * gridColSize[0];
    int cols = gridColSize[0];
    
    int mod = grid[0][0] % x;
    int cnt = 0;
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < cols; j++) {
            if (grid[i][j] % x != mod) {
                return -1;
            }
        }
    }
    
    int* flat = (int*)malloc(total * sizeof(int));
    int idx = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < cols; j++) {
            flat[idx++] = grid[i][j];
        }
    }
    
    qsort(flat, total, sizeof(int), cmp);
    
    int median = flat[total / 2];
    int operations = 0;
    
    for (int i = 0; i < total; i++) {
        operations += abs(flat[i] - median) / x;
    }
    
    free(flat);
    return operations;
}