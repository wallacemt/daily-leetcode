/**
 * Note: The returned array must be malloced, assume caller calls free().
 * Otimizações:
 * 1. Evita verificação desnecessária no loop de invocations
 * 2. Reutiliza alocações e evita duplicação de código
 * 3. Função auxiliar para cleanup
 * 4. Melhor localidade de cache
 */

static void cleanup(int** adj, int* outDegree, int* index, bool* suspicious, int* queue, int n) {
    for (int i = 0; i < n; i++) {
        free(adj[i]);
    }
    free(adj);
    free(outDegree);
    free(index);
    free(suspicious);
    free(queue);
}

int* remainingMethods(int n, int k, int** invocations, int invocationsSize, int* invocationsColSize, int* returnSize) {
    int* outDegree = calloc(n, sizeof(int));
 
    for (int i = 0; i < invocationsSize; i++) {
        outDegree[invocations[i][0]]++;
    }

    int** adj = malloc(n * sizeof(int*));
    int* index = calloc(n, sizeof(int));
 
    for (int i = 0; i < n; i++) {
        adj[i] = malloc(outDegree[i] * sizeof(int));
    } 
    for (int i = 0; i < invocationsSize; i++) {
        int u = invocations[i][0];
        adj[u][index[u]++] = invocations[i][1];
    }

    bool* suspicious = calloc(n, sizeof(bool));
    suspicious[k] = true;

    int* queue = malloc(n * sizeof(int));
    int front = 0, back = 1;
    queue[0] = k;
 
    while (front < back) {
        int u = queue[front++];

        for (int i = 0; i < outDegree[u]; i++) {
            int v = adj[u][i];

            if (!suspicious[v]) {
                suspicious[v] = true;
                queue[back++] = v;
            }
        }
    }
 
    for (int i = 0; i < invocationsSize; i++) {
        if (!suspicious[invocations[i][0]] && suspicious[invocations[i][1]]) {
            int* result = malloc(n * sizeof(int));

            for (int j = 0; j < n; j++) {
                result[j] = j;
            }

            *returnSize = n;
            cleanup(adj, outDegree, index, suspicious, queue, n);

            return result;
        }
    }
 
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += !suspicious[i];
    }

    int* result = malloc(count * sizeof(int));
    int resultIndex = 0;
 
    for (int i = 0; i < n; i++) {
        if (!suspicious[i]) {
            result[resultIndex++] = i;
        }
    }

    *returnSize = count;
    cleanup(adj, outDegree, index, suspicious, queue, n);

    return result;
}