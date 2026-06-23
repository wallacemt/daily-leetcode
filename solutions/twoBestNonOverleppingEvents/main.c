static int cmpEvents(const void *pa, const void *pb) {
    const int *a = *(const int * const *)pa;
    const int *b = *(const int * const *)pb;
    return (a[0] != b[0]) ? (a[0] - b[0]) : (a[1] - b[1]);
}

int maxTwoEvents(int **events, int eventsSize, int *eventsColSize) {
    (void)eventsColSize;

    qsort(events, eventsSize, sizeof(events[0]), cmpEvents);

    int n = eventsSize;
    int *suffix = (int *)malloc(sizeof(int) * n);

    // Construir array de sufixo com valores máximos
    suffix[n - 1] = events[n - 1][2];
    for (int i = n - 2; i >= 0; i--) {
        suffix[i] = (suffix[i + 1] > events[i][2]) ? suffix[i + 1] : events[i][2];
    }

    int res = 0;

    // Para cada evento, encontrar o próximo compatível usando busca binária
    for (int i = 0; i < n; i++) {
        int target = events[i][1] + 1;
        
        // Busca binária diretamente no array de starts (events[j][0])
        int lo = i + 1, hi = n;
        while (lo < hi) {
            int mid = lo + (hi - lo) / 2;
            if (events[mid][0] < target) lo = mid + 1;
            else hi = mid;
        }

        int val = events[i][2];
        if (lo < n) val += suffix[lo];
        
        if (val > res) res = val;
    }

    free(suffix);
    return res;
}