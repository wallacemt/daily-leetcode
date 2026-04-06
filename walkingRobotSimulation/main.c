typedef struct {
    int x, y;
} Pair;

int compare(const void* a, const void* b) {
    Pair* p1 = (Pair*)a;
    Pair* p2 = (Pair*)b;
    if (p1->x == p2->x) 
        return p1->y - p2->y;
    return p1->x - p2->x;
}

bool exists(Pair* arr, int size, int x, int y) {
    int l = 0, r = size - 1;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (arr[mid].x == x && arr[mid].y == y) 
            return true;
        if (arr[mid].x < x || (arr[mid].x == x && arr[mid].y < y)) 
            l = mid + 1;
        else r = mid - 1;
    }
    return false;
}

int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize) {

    Pair* obs = (Pair*)malloc(obstaclesSize * sizeof(Pair));
    for (int i = 0; i < obstaclesSize; i++) {
        obs[i].x = obstacles[i][0];
        obs[i].y = obstacles[i][1];
    }
    qsort(obs, obstaclesSize, sizeof(Pair), compare);

    int dirs[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int d = 0, x = 0, y = 0;
    int res = 0;

    for (int i = 0; i < commandsSize; i++) {
        int c = commands[i];
        
        if (c == -2) d = (d + 3) & 3;      // Esquerda
        else if (c == -1) d = (d + 1) & 3; // Direita
        else {
            for (int step = 0; step < c; step++) {
                int ox = x + dirs[d][0];
                int oy = y + dirs[d][1];
                
                if (!exists(obs, obstaclesSize, ox, oy)) {
                    x = ox;
                    y = oy;
                } else {
                    break; 
                }
            }
            
            int dist = x * x + y * y;
            if (dist > res) 
                res = dist;
        }
    }

    free(obs);
    return res;
}