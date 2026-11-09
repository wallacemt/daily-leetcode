#include <stdlib.h>
#include <string.h>

typedef struct {
    long long freeTime;
    int server;
} BusyServer;

// Adiciona delta à disponibilidade do servidor no BIT
static void bitAdd(int* bit, int k, int server, int delta) {
    for (int i = server + 1; i <= k; i += i & -i) {
        bit[i] += delta;
    }
}

// Retorna quantos servidores estão livres no intervalo [0, end-1]
static int bitPrefix(const int* bit, int end) {
    int result = 0;
    for (int i = end; i > 0; i -= i & -i) {
        result += bit[i];
    }
    return result;
}

// Encontra o índice do n-ésimo servidor livre (rank)
static int bitFindKth(const int* bit, int k, int rank) {
    int index = 0;
    int step = 1;
    while (step <= k) step <<= 1;
    for (step >>= 1; step > 0; step >>= 1) {
        int next = index + step;
        if (next <= k && bit[next] < rank) {
            index = next;
            rank -= bit[next];
        }
    }
    return index; // Retorna índice 0-based (o BIT usa 1-based internamente)
}

// Comparador para a Min-Heap (prioridade: tempo menor, depois índice menor)
static int busyLess(BusyServer a, BusyServer b) {
    if (a.freeTime != b.freeTime) return a.freeTime < b.freeTime;
    return a.server < b.server;
}

static void busyPush(BusyServer* heap, int* size, BusyServer value) {
    int i = (*size)++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!busyLess(value, heap[p])) break;
        heap[i] = heap[p];
        i = p;
    }
    heap[i] = value;
}

static BusyServer busyPop(BusyServer* heap, int* size) {
    BusyServer root = heap[0];
    BusyServer last = heap[--(*size)];
    if (*size > 0) {
        int i = 0;
        while (1) {
            int child = i * 2 + 1;
            if (child >= *size) break;
            if (child + 1 < *size && busyLess(heap[child + 1], heap[child])) child++;
            if (!busyLess(heap[child], last)) break;
            heap[i] = heap[child];
            i = child;
        }
        heap[i] = last;
    }
    return root;
}

int* busiestServers(int k, int* arrival, int arrivalSize, int* load, int loadSize, int* returnSize) {
    int* bit = malloc((k + 1) * sizeof(int));
    int* count = calloc(k, sizeof(int));
    int* answer = malloc(k * sizeof(int));
    BusyServer* busy = malloc(k * sizeof(BusyServer));

    if (!bit || !count || !answer || !busy) {
        free(bit); free(count); free(answer); free(busy);
        *returnSize = 0; return NULL;
    }

    // Inicialização O(k) do BIT com todos os servidores disponíveis (valor 1)
    for (int i = 1; i <= k; i++) bit[i] = i & -i;

    int busySize = 0, availableCount = k, maxRequests = 0;

    for (int i = 0; i < arrivalSize; i++) {
        long long now = arrival[i];
        
        // 1. Liberar servidores que já terminaram a tarefa
        while (busySize > 0 && busy[0].freeTime <= now) {
            BusyServer s = busyPop(busy, &busySize);
            bitAdd(bit, k, s.server, 1);
            availableCount++;
        }

        if (availableCount == 0) continue;

        // 2. Lógica circular de busca
        int preferred = i % k;
        int freeBefore = bitPrefix(bit, preferred);
        int freeTotal = availableCount;
        
        int rank;
        // Se há servidores livres de 'preferred' até o fim
        if (freeTotal - freeBefore > 0) {
            rank = freeBefore + 1;
        } else {
            // Volta para o início
            rank = 1;
        }

        int server = bitFindKth(bit, k, rank);
        
        // 3. Atribuir tarefa
        bitAdd(bit, k, server, -1);
        availableCount--;
        count[server]++;
        if (count[server] > maxRequests) maxRequests = count[server];

        BusyServer assigned = { now + load[i], server };
        busyPush(busy, &busySize, assigned);
    }

    int resIdx = 0;
    for (int i = 0; i < k; i++) {
        if (count[i] == maxRequests) answer[resIdx++] = i;
    }

    free(bit); free(count); free(busy);
    *returnSize = resIdx;
    return answer;
}
