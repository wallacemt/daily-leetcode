bool hasValidPath(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];

    // Tabela de direções: quais saídas cada cano suporta
    // [cano][direção] = true/false
    static const bool dirs[7][4] = {
        {false, false, false, false}, 
        {true,  true,  false, false}, 
        {false, false, true,  true }, 
        {true,  false, false, true }, 
        {false, true,  false, true }, 
        {true,  false, true,  false}, 
        {false, true,  true,  false}  
    };

    static const int moves[4][4] = {
        {0, -1, 0, 1}, 
        {0, 1, 1, 0},  
        {-1, 0, 2, 3}, 
        {1, 0, 3, 2}   
    };

    bool* visited = (bool*)calloc(rows * cols, sizeof(bool));
    if (!visited) return false;

    // Fila com estrutura única (melhor localidade de cache)
    typedef struct {
        int r;
        int c;
    } Cell;
    
    Cell* queue = (Cell*)malloc(rows * cols * sizeof(Cell));
    if (!queue) {
        free(visited);
        return false;
    }

    int head = 0, tail = 0;

    // Inicialização
    queue[tail].r = 0;
    queue[tail].c = 0;
    tail++;
    visited[0] = true;

    while (head < tail) {
        int r = queue[head].r;
        int c = queue[head].c;
        head++;

        // Verificação de chegada
        if (r == rows - 1 && c == cols - 1) {
            free(visited);
            free(queue);
            return true;
        }

        for (int i = 0; i < 4; i++) {
            int nr = r + moves[i][0];
            int nc = c + moves[i][1];

            if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) 
                continue;

            int visitIdx = nr * cols + nc;
            if (visited[visitIdx]) 
                continue;

            int outDir = moves[i][2];
            int inDir = moves[i][3];
            int currPipe = grid[r][c];
            int nextPipe = grid[nr][nc];

            // Validação de conexão
            if (dirs[currPipe][outDir] && dirs[nextPipe][inDir]) {
                visited[visitIdx] = true;
                queue[tail].r = nr;
                queue[tail].c = nc;
                tail++;
            }
        }
    }

    free(visited);
    free(queue);
    return false;
}