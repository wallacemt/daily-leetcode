int countUnguarded(int m, int n, int** guards, int guardsSize, int* guardsColSize, int** walls, int wallsSize, int* wallsColSize) {

    int** grid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        grid[i] = (int*)calloc(n, sizeof(int));
    }
    
    for (int i = 0; i < guardsSize; i++) {
        grid[guards[i][0]][guards[i][1]] = 1;
    }
    
    for (int i = 0; i < wallsSize; i++) {
        grid[walls[i][0]][walls[i][1]] = 2;
    }
    
    int dirs[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
    
    for (int i = 0; i < guardsSize; i++) {
        int row = guards[i][0];
        int col = guards[i][1];
        
        for (int d = 0; d < 4; d++) {
            int r = row + dirs[d][0];
            int c = col + dirs[d][1];
            
            while (r >= 0 && r < m && c >= 0 && c < n) {
                if (grid[r][c] == 1 || grid[r][c] == 2) break; 
                grid[r][c] = 3; 
                r += dirs[d][0];
                c += dirs[d][1];
            }
        }
    }
    
    int count = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) count++;
        }
    }
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }
    free(grid);
    
    return count;
}