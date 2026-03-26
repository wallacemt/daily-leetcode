
#define HASH_SIZE 200003
typedef struct {
    long long* keys;
    bool* used;
} HashSet;

HashSet* createSet() {
    HashSet* set = (HashSet*)malloc(sizeof(HashSet));
    set->keys = (long long*)malloc(HASH_SIZE * sizeof(long long));
    set->used = (bool*)calloc(HASH_SIZE, sizeof(bool));
    return set;
}

void insertSet(HashSet* set, long long val) {
    unsigned int h = (unsigned int)(val % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    while (set->used[h]) {
        if (set->keys[h] == val) 
            return;
        h = (h + 1) % HASH_SIZE;
    }
    set->keys[h] = val;
    set->used[h] = true;
}

bool findSet(HashSet* set, long long val) {
    unsigned int h = (unsigned int)(val % HASH_SIZE + HASH_SIZE) % HASH_SIZE;
    while (set->used[h]) {
        if (set->keys[h] == val) 
            return true;
        h = (h + 1) % HASH_SIZE;
    }
    return false;
}

void freeSet(HashSet* set) {
    free(set->keys);
    free(set->used);
    free(set);
}

void freeGrid(int** g, int rows) {
    for (int i = 0; i < rows; i++) 
        free(g[i]);
    free(g);
}


int** rotation(int** grid, int rows, int cols, int* newRows, int* newCols) {
    *newRows = cols;
    *newCols = rows;
    int** tmp = (int**)malloc(cols * sizeof(int*));
    for (int i = 0; i < cols; i++) {
        tmp[i] = (int*)malloc(rows * sizeof(int));
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            tmp[j][rows - 1 - i] = grid[i][j];
        }
    }
    return tmp;
}

bool canPartitionGrid(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    long long total = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            total += (long long)grid[i][j];
        }
    }

    int** curGrid = grid;
    int curR = rows;
    int curC = cols;

    for (int rot = 0; rot < 4; rot++) {
        HashSet* visited = createSet();
        insertSet(visited, 0);
        long long vals = 0;

        bool found = false;
        if (curR >= 2) {
            if (curC == 1) {
                for (int i = 0; i < curR - 1; i++) {
                    vals += curGrid[i][0];
                    long long flag = vals * 2 - total;
                    if (flag == 0 || flag == curGrid[0][0] || flag == curGrid[i][0]) {
                        found = true; 
                            break;
                    }
                }
            } else {
                for (int i = 0; i < curR - 1; i++) {
                    for (int j = 0; j < curC; j++) {
                        insertSet(visited, (long long)curGrid[i][j]);
                        vals += curGrid[i][j];
                    }
                    long long flag = vals * 2 - total;
                    if (i == 0) {
                        if (flag == 0 || flag == curGrid[0][0] || flag == curGrid[0][curC - 1]) {
                            found = true; 
                                break;
                        }
                    } else {
                        if (findSet(visited, flag)) {
                            found = true; 
                                break;
                        }
                    }
                }
            }
        }

        freeSet(visited);
        if (found) {
            if (curGrid != grid) freeGrid(curGrid, curR);
            return true;
        }

        int nextR, nextC;
        int** nextGrid = rotation(curGrid, curR, curC, &nextR, &nextC);
        if (curGrid != grid) 
            freeGrid(curGrid, curR);
        curGrid = nextGrid;
        curR = nextR;
        curC = nextC;
    }

    if (curGrid != grid) 
        freeGrid(curGrid, curR);
    return false;
}
