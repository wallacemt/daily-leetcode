typedef long long ll;

typedef struct {
    int val;
    int idx;
} Cell;

static int cmpCellDesc(const void* a, const void* b) {
    int diff = ((const Cell*)b)->val - ((const Cell*)a)->val;
    if (diff != 0) return diff;
    return ((const Cell*)a)->idx - ((const Cell*)b)->idx;
}

static ll minll(ll a, ll b) {
    return a < b ? a : b;
}

int minCost(int** grid, int gridSize, int* gridColSize, int k) {
    int m = gridSize;
    int n = gridColSize[0];
    const ll INF = (ll)1e30;
    int total = m * n;

    Cell* cells = (Cell*)malloc(sizeof(Cell) * total);
    ll* dist = (ll*)malloc(sizeof(ll) * total);
    ll* nextDist = (ll*)malloc(sizeof(ll) * total);

    dist[0] = 0;
    for (int i = 1; i < total; i++) 
        dist[i] = INF;

    int pos = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cells[pos++] = (Cell){grid[i][j], i * n + j};
        }
    }
    qsort(cells, total, sizeof(Cell), cmpCellDesc);

    ll best = INF;

    for (int t = 0; t <= k; t++) {
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int idx = i * n + j;
                ll cur = dist[idx];
                
                if (cur < INF) {
                    if (j + 1 < n) {
                        ll newDist = cur + grid[i][j + 1];
                        if (newDist < dist[idx + 1]) 
                            dist[idx + 1] = newDist;
                    }
                    if (i + 1 < m) {
                        ll newDist = cur + grid[i + 1][j];
                        if (newDist < dist[idx + n]) 
                            dist[idx + n] = newDist;
                    }
                }
            }
        }

        best = minll(best, dist[total - 1]);
        
        if (t == k) break;

        for (int i = 0; i < total; i++) 
            nextDist[i] = INF;

        ll move = INF;

        for (int p = 0; p < total; ) {
            int val = cells[p].val;
            ll group_min = INF;
            
            int q = p;
            while (q < total && cells[q].val == val) {
                ll d = dist[cells[q].idx];
                if (d < group_min) 
                    group_min = d;
                q++;
            }
            
            move = minll(move, group_min);
            
            for (int t2 = p; t2 < q; t2++) {
                nextDist[cells[t2].idx] = move;
            }
            
            p = q;
        }

        ll* temp = dist;
        dist = nextDist;
        nextDist = temp;
    }

    free(nextDist);
    free(dist);
    free(cells);
    
    return (best >= INF) ? -1 : (int)best;
}