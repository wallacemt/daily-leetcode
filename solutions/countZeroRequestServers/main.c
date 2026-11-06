#include <stdlib.h>

typedef struct {
    int time;
    int index;
} Query;

// Comparador para ordenar os logs por tempo
int compareLogs(const void* a, const void* b) {
    const int* x = *(const int**)a;
    const int* y = *(const int**)b;

    return (x[1] > y[1]) - (x[1] < y[1]);
}

// Comparador para ordenar as consultas por tempo
int compareQueries(const void* a, const void* b) {
    const Query* x = (const Query*)a;
    const Query* y = (const Query*)b;

    if (x->time != y->time) {
        return (x->time > y->time) - (x->time < y->time);
    }

    return (x->index > y->index) - (x->index < y->index);
}

// Função para contar servidores inativos
int* countServers(int n, int** logs, int logsSize, int* logsColSize,
                  int x, int* queries, int queriesSize,
                  int* returnSize) {
    qsort(logs, logsSize, sizeof(int*), compareLogs);

    Query* sortedQueries = malloc(queriesSize * sizeof(Query));
    int* ans = calloc(queriesSize, sizeof(int));
    int* freq = calloc(n + 1, sizeof(int));

    if (!sortedQueries || !ans || !freq) {
        // Verificação de alocação de memória
        return NULL;
    }

    for (int i = 0; i < queriesSize; i++) {
        sortedQueries[i].time = queries[i];
        sortedQueries[i].index = i;
    }

    qsort(sortedQueries, queriesSize, sizeof(Query), compareQueries);

    int left = 0, right = 0, active = 0;

    for (int i = 0; i < queriesSize; i++) {
        int t = sortedQueries[i].time;

        // Adiciona logs até o tempo da consulta
        while (right < logsSize && logs[right][1] <= t) {
            int server = logs[right][0];

            if (freq[server] == 0) {
                active++;
            }

            freq[server]++;
            right++;
        }

        // Remove logs que estão fora do intervalo de interesse
        while (left < right && logs[left][1] < t - x) {
            int server = logs[left][0];

            freq[server]--;

            if (freq[server] == 0) {
                active--;
            }

            left++;
        }

        // O número de servidores inativos é total - servidores ativos
        ans[sortedQueries[i].index] = n - active;
    }

    free(sortedQueries);
    free(freq);

    *returnSize = queriesSize;
    return ans;
}

