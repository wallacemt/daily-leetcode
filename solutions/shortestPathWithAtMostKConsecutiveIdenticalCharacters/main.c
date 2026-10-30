#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int v, w, next;
    bool same;
} Edge;

typedef struct {
    long long d;
    int u, r;
} State;

typedef struct {
    State* data;
    int size, capacity;
} MinHeap;

static bool less(State a, State b) {
    if (a.d != b.d) return a.d < b.d;
    if (a.u != b.u) return a.u < b.u;
    return a.r < b.r;
}

static void push(MinHeap* heap, State value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, heap->capacity * sizeof(State));
        if (!heap->data) {
            perror("Failed to reallocate memory for MinHeap");
            exit(EXIT_FAILURE);
        }
    }

    int i = heap->size++;
    while (i > 0) {
        int p = (i - 1) / 2;
        if (!less(value, heap->data[p])) break;
        heap->data[i] = heap->data[p];
        i = p;
    }
    heap->data[i] = value;
}

static State pop(MinHeap* heap) {
    State result = heap->data[0];
    State last = heap->data[--heap->size];

    if (heap->size == 0) return result;

    int i = 0;
    while (2 * i + 1 < heap->size) {
        int child = 2 * i + 1;
        if (child + 1 < heap->size && less(heap->data[child + 1], heap->data[child])) {
            child++;
        }
        if (!less(heap->data[child], last)) break;
        heap->data[i] = heap->data[child];
        i = child;
    }
    heap->data[i] = last;
    return result;
}

int shortestPath(int n, int** edges, int edgesSize, int* edgesColSize, char* labels, int k) {
    (void)edgesColSize;

    int* head = malloc(n * sizeof(int));
    int* done = malloc(n * sizeof(int));
    Edge* graph = malloc((edgesSize > 0 ? edgesSize : 1) * sizeof(Edge));

    if (!head || !done || !graph) {
        perror("Failed to allocate memory");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        head[i] = -1;
        done[i] = k + 1; // Inicializa com um valor maior que k
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        graph[i] = (Edge){v, edges[i][2], head[u], labels[u] == labels[v]};
        head[u] = i;
    }

    MinHeap heap = {malloc(16 * sizeof(State)), 0, 16};
    if (!heap.data) {
        perror("Failed to allocate memory for MinHeap");
        exit(EXIT_FAILURE);
    }

    push(&heap, (State){0, 0, 1});
    int answer = -1;

    while (heap.size > 0) {
        State current = pop(&heap);
        long long d = current.d;
        int u = current.u;
        int r = current.r;

        if (r >= done[u]) continue;

        done[u] = r;

        if (u == n - 1) {
            answer = (int)d;
            break;
        }

        for (int i = head[u]; i != -1; i = graph[i].next) {
            Edge e = graph[i];
            int nr = e.same ? r + 1 : 1;

            if (nr < done[e.v]) {
                push(&heap, (State){d + e.w, e.v, nr});
            }
        }
    }

    free(head);
    free(done);
    free(graph);
    free(heap.data);

    return answer;
}
