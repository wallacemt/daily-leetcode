#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// Union-Find com compressão de caminho e união por rank
typedef struct {
    int* parent;
    int* rank;
} UnionFind;

int find(UnionFind* uf, int x) {
    if (uf->parent[x] != x) {
        uf->parent[x] = find(uf, uf->parent[x]); // Compressão de caminho
    }
    return uf->parent[x];
}

void unite(UnionFind* uf, int a, int b) {
    a = find(uf, a);
    b = find(uf, b);
    if (a == b) return;

    // União por rank
    if (uf->rank[a] < uf->rank[b]) {
        uf->parent[a] = b;
    } else if (uf->rank[a] > uf->rank[b]) {
        uf->parent[b] = a;
    } else {
        uf->parent[b] = a;
        uf->rank[a]++;
    }
}

int latestDayToCross(int row, int col, int** cells, int cellsSize, int* cellsColSize) {
    int n = row * col;
    int top = n, bottom = n + 1;

    UnionFind uf;
    uf.parent = (int*)malloc((n + 2) * sizeof(int));
    uf.rank = (int*)calloc(n + 2, sizeof(int));
    bool* land = (bool*)calloc(n, sizeof(bool));

    for (int i = 0; i < n + 2; i++) {
        uf.parent[i] = i;
    }

    int dr[] = {0, 0, 1, -1};
    int dc[] = {1, -1, 0, 0};

    for (int d = cellsSize - 1; d >= 0; d--) {
        int r = cells[d][0] - 1;
        int c = cells[d][1] - 1;
        int id = r * col + c;

        land[id] = true;

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < row && nc >= 0 && nc < col) {
                int nid = nr * col + nc;
                if (land[nid]) {
                    unite(&uf, id, nid);
                }
            }
        }

        if (r == 0) {
            unite(&uf, id, top);
        }

        if (r == row - 1) {
            unite(&uf, id, bottom);
        }

        if (find(&uf, top) == find(&uf, bottom)) {
            free(uf.parent);
            free(uf.rank);
            free(land);
            return d; 
        }
    }

    free(uf.parent);
    free(uf.rank);
    free(land);
    return 0;
}