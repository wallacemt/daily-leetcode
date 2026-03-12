typedef struct {
    int u, v, w, idx;
} Edge;

int compareEdges(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeB->w - edgeA->w;
}

int findParent(int v, int* parent) {
    if (parent[v] == v) return v;
    return parent[v] = findParent(parent[v], parent);
}

int unionSets(int a, int b, int* parent, int* size) {
    a = findParent(a, parent);
    b = findParent(b, parent);
    if (a != b) {
        if (size[a] < size[b]) {
            int temp = a; a = b; b = temp;
        }
        parent[b] = a;
        size[a] += size[b];
        return 1; 
    }
    return 0;
}
int maxStability(int n, int** edges, int edgesSize, int* edgesColSize, int k) {
    int* parent = (int*)malloc(n * sizeof(int));
    int* size = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        size[i] = 1;
    }

    int comp = n;
    int res = INT_MAX;

    // Processar edges obrigatórios
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][3] == 1) {
            if (unionSets(edges[i][0], edges[i][1], parent, size)) {
                comp--;
                res = (edges[i][2] < res) ? edges[i][2] : res;
            } else {
                free(parent); 
                free(size);
                return -1;
            }
        }
    }

    if (comp == 1) {
        free(parent); 
        free(size);
        return res;
    }

    // Contar edges opcionais
    int optCount = 0;
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][3] == 0) optCount++;
    }

    Edge* opt = (Edge*)malloc(optCount * sizeof(Edge));
    int idx = 0;
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][3] == 0) {
            opt[idx].u = edges[i][0];
            opt[idx].v = edges[i][1];
            opt[idx].w = edges[i][2];
            opt[idx].idx = i;
            idx++;
        }
    }

    qsort(opt, optCount, sizeof(Edge), compareEdges);

    int* stab = (int*)malloc(optCount * sizeof(int)); // Aloca apenas optCount
    int stabCount = 0;
    for (int i = 0; i < optCount; i++) {
        if (unionSets(opt[i].u, opt[i].v, parent, size)) {
            comp--;
            stab[stabCount++] = opt[i].w;
            if (comp == 1) break;
        }
    }

    if (comp > 1) {
        free(parent); 
        free(size); 
        free(opt); 
        free(stab);
        return -1;
    }

    // Aplicar multiplicação por 2 nos últimos k elementos
    for (int i = 1; i <= k && i <= stabCount; i++) {
        stab[stabCount - i] *= 2;
    }

    // Encontrar mínimo
    int minStab = INT_MAX;
    for (int i = 0; i < stabCount; i++) {
        minStab = (stab[i] < minStab) ? stab[i] : minStab;
    }

    int finalRes = (res < minStab) ? res : minStab;
    
    free(parent);
    free(size);
    free(opt);
    free(stab);

    return finalRes;
}
