typedef struct Edge {
    int to;
    int w;
    int next;
} Edge;

typedef struct {
    int dist;
    int node;
} HeapItem;

typedef struct {
    HeapItem *a;
    int size;
    int cap;
} MinHeap;

static void heapInit(MinHeap *h, int cap) {
    h->a = (HeapItem*)malloc(sizeof(HeapItem) * cap);
    h->size = 0;
    h->cap = cap;
}
static void heapFree(MinHeap *h) { free(h->a); }

static inline int less(HeapItem x, HeapItem y) {
    return x.dist != y.dist ? x.dist < y.dist : x.node < y.node;
}

static void heapPush(MinHeap *h, int dist, int node) {
    int i = h->size++;
    h->a[i].dist = dist;
    h->a[i].node = node;
    while (i > 0) {
        int p = (i - 1) >> 1;
        if (less(h->a[p], h->a[i])) 
            break;
        HeapItem t = h->a[p]; 
        h->a[p] = h->a[i]; 
        h->a[i] = t;
        i = p;
    }
}

static HeapItem heapPop(MinHeap *h) {
    HeapItem res = h->a[0];
    h->a[0] = h->a[--h->size];
    int i = 0;
    while (1) {
        int l = (i << 1) + 1, r = l + 1, s = i;
        if (l < h->size && less(h->a[l], h->a[s])) 
            s = l;
        if (r < h->size && less(h->a[r], h->a[s])) 
            s = r;
        if (s == i) 
            break;
        HeapItem t = h->a[s]; 
        h->a[s] = h->a[i]; 
        h->a[i] = t;
        i = s;
    }
    return res;
}

int minCost(int n, int** edges, int edgesSize, int* edgesColSize) {
    (void)edgesColSize;

    int m = edgesSize;
    int *head = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) 
        head[i] = -1;

    Edge *E = (Edge*)malloc(sizeof(Edge) * (m << 1));
    int ecnt = 0;

    for (int i = 0; i < m; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        
        E[ecnt].to = v;
        E[ecnt].w = w;
        E[ecnt].next = head[u];
        head[u] = ecnt++;
        
        E[ecnt].to = u;
        E[ecnt].w = w << 1;
        E[ecnt].next = head[v];
        head[v] = ecnt++;
    }

    int *ans = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) 
        ans[i] = INT_MAX;
    ans[0] = 0;

    MinHeap pq;
    heapInit(&pq, (m << 1) + 10);
    heapPush(&pq, 0, 0);

    while (pq.size > 0) {
        HeapItem cur = heapPop(&pq);
        int weight = cur.dist;
        int node = cur.node;

        if (weight > ans[node]) 
            continue;

        for (int ei = head[node]; ei != -1; ei = E[ei].next) {
            int nd = E[ei].to;
            int wt = E[ei].w;
            int newDist = weight + wt;
            if (newDist < ans[nd]) {
                ans[nd] = newDist;
                heapPush(&pq, newDist, nd);
            }
        }
    }

    int ret = (ans[n - 1] == INT_MAX) ? -1 : ans[n - 1];

    heapFree(&pq);
    free(ans);
    free(E);
    free(head);
    return ret;
}