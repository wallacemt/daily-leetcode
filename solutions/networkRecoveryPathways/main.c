#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef struct Edge {
    int to;
    int weight;
    struct Edge* next;
} Edge;

typedef struct {
    long long cost;
    int node;
} HeapNode;

// Pool de alocação para evitar múltiplos malloc
typedef struct {
    Edge* edges;
    int edgeCount;
    int capacity;
} EdgePool;

EdgePool* createEdgePool(int capacity) {
    EdgePool* pool = (EdgePool*)malloc(sizeof(EdgePool));
    pool->edges = (Edge*)malloc(capacity * sizeof(Edge));
    pool->capacity = capacity;
    pool->edgeCount = 0;
    return pool;
}

Edge* allocateEdge(EdgePool* pool) {
    if (pool->edgeCount >= pool->capacity) {
        pool->capacity *= 2;
        pool->edges = (Edge*)realloc(pool->edges, pool->capacity * sizeof(Edge));
    }
    return &pool->edges[pool->edgeCount++];
}

void freeEdgePool(EdgePool* pool) {
    free(pool->edges);
    free(pool);
}

void addEdge(Edge** graph, int from, int to, int weight, EdgePool* pool) {
    Edge* edge = allocateEdge(pool);
    edge->to = to;
    edge->weight = weight;
    edge->next = graph[from];
    graph[from] = edge;
}

// Heap otimizado com alocação pré-dimensionada
typedef struct {
    HeapNode* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    // Pré-alocar com margem para evitar realocações
    heap->data = (HeapNode*)malloc((capacity + 1) * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void freeHeap(MinHeap* heap) {
    free(heap->data);
    free(heap);
}

void resetHeap(MinHeap* heap) {
    heap->size = 0;
}

void push(MinHeap* heap, HeapNode node) {
    // CRÍTICO: Garantir que nunca realocamos durante operação
    if (heap->size >= heap->capacity) {
        // Isto NÃO deve acontecer se dimensionarmos corretamente
        fprintf(stderr, "ERRO: Heap capacity insuficiente!\n");
        exit(1);
    }

    int i = ++heap->size;
    heap->data[i] = node;

    // Bubble up
    while (i > 1 && heap->data[i].cost < heap->data[i / 2].cost) {
        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[i / 2];
        heap->data[i / 2] = temp;
        i /= 2;
    }
}

HeapNode pop(MinHeap* heap) {
    HeapNode top = heap->data[1];
    heap->data[1] = heap->data[heap->size--];

    int i = 1;
    while (i * 2 <= heap->size) {
        int j = i * 2;
        if (j + 1 <= heap->size && heap->data[j + 1].cost < heap->data[j].cost)
            j++;

        if (heap->data[i].cost <= heap->data[j].cost)
            break;

        HeapNode temp = heap->data[i];
        heap->data[i] = heap->data[j];
        heap->data[j] = temp;
        i = j;
    }

    return top;
}

bool check(int minWeight, Edge** graph, bool* online, int n, long long k, MinHeap* heap, long long* bestCost) {
    // Limpar estado anterior
    resetHeap(heap);
    for (int i = 0; i < n; i++) {
        bestCost[i] = LLONG_MAX;
    }

    push(heap, (HeapNode){0, 0});
    bestCost[0] = 0;

    while (heap->size > 0) {
        HeapNode cur = pop(heap);
        long long currentCost = cur.cost;
        int currentNode = cur.node;

        if (currentNode == n - 1) {
            return true;
        }

        // Poda: se já encontramos caminho melhor, ignora
        if (currentCost > bestCost[currentNode]) {
            continue;
        }

        for (Edge* edge = graph[currentNode]; edge != NULL; edge = edge->next) {
            int nextNode = edge->to;
            int edgeWeight = edge->weight;

            // Validações em ordem de custo computacional
            if (edgeWeight < minWeight) continue;
            if (!online[nextNode]) continue;

            long long newCost = currentCost + edgeWeight;
            if (newCost > k) continue;

            if (newCost < bestCost[nextNode]) {
                bestCost[nextNode] = newCost;
                push(heap, (HeapNode){newCost, nextNode});
            }
        }
    }

    return false;
}

int findMaxPathScore(int** edges, int edgesSize, int* edgesColSize, bool* online, int onlineSize, long long k) {
    int maxWeight = 0;
    Edge** graph = (Edge**)calloc(onlineSize, sizeof(Edge*));

    // Pool de alocação para edges
    EdgePool* pool = createEdgePool(edgesSize + 10);

    for (int i = 0; i < edgesSize; i++) {
        int fromNode = edges[i][0];
        int toNode = edges[i][1];
        int weight = edges[i][2];

        addEdge(graph, fromNode, toNode, weight, pool);

        if (weight > maxWeight) {
            maxWeight = weight;
        }
    }

    // Heap pré-dimensionado: no pior caso, cada edge é visitado uma vez
    // Margem: edgesSize * 2 para segurança
    MinHeap* heap = createHeap(edgesSize * 2 + 100);
    long long* bestCost = (long long*)malloc(onlineSize * sizeof(long long));

    int left = 0;
    int right = maxWeight;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (check(mid, graph, online, onlineSize, k, heap, bestCost)) {
            result = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // Limpeza
    freeHeap(heap);
    free(bestCost);
    freeEdgePool(pool);
    free(graph);

    return result;
}