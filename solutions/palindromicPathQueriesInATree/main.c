#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define ALPHABET_SIZE 26

static void update(uint32_t* seg, int size2, int p, uint32_t value) {
    p += size2;
    seg[p] = value;

    for (p >>= 1; p; p >>= 1) {
        seg[p] = seg[p * 2] ^ seg[p * 2 + 1];
    }
}

static uint32_t rangeQuery(const uint32_t* seg, int size2, int l, int r) {
    l += size2;
    r += size2;
    uint32_t res = 0;

    while (l <= r) {
        if (l & 1) res ^= seg[l++];
        if (!(r & 1)) res ^= seg[r--];

        l >>= 1;
        r >>= 1;
    }

    return res;
}

static uint32_t pathQuery(const uint32_t* seg, int size2, const int* parent, const int* depth, const int* head, const int* pos, int u, int v) {
    uint32_t res = 0;

    while (head[u] != head[v]) {
        if (depth[head[u]] < depth[head[v]]) {
            int temp = u;
            u = v;
            v = temp;
        }

        res ^= rangeQuery(seg, size2, pos[head[u]], pos[u]);
        u = parent[head[u]];
    }

    if (depth[u] > depth[v]) {
        int temp = u;
        u = v;
        v = temp;
    }

    return res ^ rangeQuery(seg, size2, pos[u], pos[v]);
}

bool* palindromePath(int n, int** edges, int edgesSize, int* edgesColSize, char* s, char** queries, int queriesSize, int* returnSize) {
    (void)edgesColSize;

    // Alocação de memória
    int* first = calloc(n, sizeof(int));
    int edgeCapacity = edgesSize > 0 ? 2 * edgesSize : 1;
    int* to = malloc(edgeCapacity * sizeof(int));
    int* next = malloc(edgeCapacity * sizeof(int));

    for (int i = 0; i < n; ++i) first[i] = -1;

    // Construção da lista de adjacência
    int edgeCount = 0;
    for (int i = 0; i < edgesSize; ++i) {
        int u = edges[i][0];
        int v = edges[i][1];

        to[edgeCount] = v;
        next[edgeCount] = first[u];
        first[u] = edgeCount++;

        to[edgeCount] = u;
        next[edgeCount] = first[v];
        first[v] = edgeCount++;
    }

    // Inicialização das variáveis
    int* parent = malloc(n * sizeof(int));
    int* depth = calloc(n, sizeof(int));
    int* order = malloc(n * sizeof(int));
    int* size = malloc(n * sizeof(int));
    int* heavy = malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
        size[i] = 1;
        heavy[i] = -1;
    }

    parent[0] = 0;
    order[0] = 0;
    int orderSize = 1;

    // DFS para construir a árvore
    for (int i = 0; i < orderSize; ++i) {
        int u = order[i];

        for (int e = first[u]; e != -1; e = next[e]) {
            int v = to[e];

            if (v != parent[u]) {
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order[orderSize++] = v;
            }
        }
    }

    // Cálculo do tamanho e do caminho pesado
    for (int i = orderSize - 1; i > 0; --i) {
        int u = order[i];
        int p = parent[u];

        size[p] += size[u];

        if (heavy[p] == -1 || size[u] > size[heavy[p]]) {
            heavy[p] = u;
        }
    }

    // Estruturas para HLD
    int* head = malloc(n * sizeof(int));
    int* pos = malloc(n * sizeof(int));
    int* stack = malloc(n * sizeof(int));

    int top = 0;
    int cur = 0;
    stack[top++] = 0;

    while (top > 0) {
        int u = stack[--top];
        int h = u;

        while (u != -1) {
            head[u] = h;
            pos[u] = cur++;

            for (int e = first[u]; e != -1; e = next[e]) {
                int v = to[e];

                if (v != parent[u] && v != heavy[u]) {
                    stack[top++] = v;
                }
            }

            u = heavy[u];
        }
    }

    // Criação da árvore de segmentos
    int size2 = 1;
    while (size2 < n) size2 <<= 1;

    uint32_t* seg = calloc(2 * size2, sizeof(uint32_t));

    for (int u = 0; u < n; ++u) {
        seg[size2 + pos[u]] = 1u << (s[u] - 'a');
    }

    for (int i = size2 - 1; i > 0; --i) {
        seg[i] = seg[i * 2] ^ seg[i * 2 + 1];
    }

    // Processamento das consultas
    bool* ans = malloc((queriesSize > 0 ? queriesSize : 1) * sizeof(bool));
    *returnSize = 0;

    for (int i = 0; i < queriesSize; ++i) {
        const char* q = queries[i];

        if (strncmp(q, "update", 6) == 0) {
            int u;
            char c;
            sscanf(q, "%*s %d %c", &u, &c);
            update(seg, size2, pos[u], 1u << (c - 'a'));
        } else {
            int u, v;
            sscanf(q, "%*s %d %d", &u, &v);

            uint32_t mask = pathQuery(seg, size2, parent, depth, head, pos, u, v);
            ans[(*returnSize)++] = (mask & (mask - 1u)) == 0; // Verifica se é palíndromo
        }
    }

    // Liberação de memória
    free(first);
    free(to);
    free(next);
    free(parent);
    free(depth);
    free(order);
    free(size);
    free(heavy);
    free(head);
    free(pos);
    free(stack);
    free(seg);

    return ans;
}
