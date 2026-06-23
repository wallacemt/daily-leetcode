int cmp(const void* a, const void* b) {
    int x = (*(int**)a)[0];
    int y = (*(int**)b)[0];
    if (x < y) return -1;
    if (x > y) return 1;
    return 0;
}

int maxBuilding(int n, int** restrictions, int restrictionsSize, int* restrictionsColSize) {
    if (restrictionsSize == 0) {
        return n - 1;
    }

    qsort(restrictions, restrictionsSize, sizeof(int*), cmp);

    int idx = 1, h = 0;
    for (int i = 0; i < restrictionsSize; i++) {
        int x = restrictions[i][0];
        int y = restrictions[i][1];
        
        int limit = x - idx + h;
        if (y > limit) {
            restrictions[i][1] = limit;
        }
        
        idx = x;
        h = restrictions[i][1];
    }

    for (int i = restrictionsSize - 2; i >= 0; i--) {
        int limit = restrictions[i + 1][1] + restrictions[i + 1][0] - restrictions[i][0];
        if (limit < restrictions[i][1]) {
            restrictions[i][1] = limit;
        }
    }

    int final_x = restrictions[restrictionsSize - 1][0];
    int final_h = restrictions[restrictionsSize - 1][1];
    int res = n - final_x + final_h;


    idx = 1;
    h = 0;
    for (int i = 0; i < restrictionsSize; i++) {
        int x = restrictions[i][0];
        int y = restrictions[i][1];
        
        int diff = (y > h) ? (y - h) : (h - y);
        int steps = x - idx - diff;
        int higher = (y > h) ? y : h;
        
        int candidate = higher + (steps >> 1);
        if (candidate > res) {
            res = candidate;
        }
        
        idx = x;
        h = y;
    }

    return res;
}