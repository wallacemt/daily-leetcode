#include <string.h>
#include <stdlib.h>

typedef struct {
    int safe;
    int r;
    int c;
} Node;
 
typedef struct {
    Node* data;
    int size;
    int capacity;
} MaxHeap;

MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = malloc(sizeof(MaxHeap));
    heap->data = malloc(capacity * sizeof(Node));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void freeHeap(MaxHeap* heap) {
    free(heap->data);
    free(heap);
}

static inline void swap(Node* a, Node* b) {
    Node temp = *a;
    *a = *b;
    *b = temp;
}

void push(MaxHeap* heap, Node node) {
    if (heap->size == heap->capacity) return;

    int i = heap->size++;
    heap->data[i] = node;
 
    while (i > 0) {
        int parent = (i - 1) >> 1;
        if (heap->data[i].safe <= heap->data[parent].safe) break;
        swap(&heap->data[i], &heap->data[parent]);
        i = parent;
    }
}

Node pop(MaxHeap* heap) {
    Node top = heap->data[0];
    heap->data[0] = heap->data[--heap->size];

    int i = 0;
    while (1) {
        int left = (i << 1) + 1;
        int right = left + 1;
        int largest = i;

        if (left < heap->size && heap->data[left].safe > heap->data[largest].safe)
            largest = left;
        if (right < heap->size && heap->data[right].safe > heap->data[largest].safe)
            largest = right;

        if (largest == i) break;

        swap(&heap->data[i], &heap->data[largest]);
        i = largest;
    }

    return top;
}

int maximumSafenessFactor(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;

    if (grid[0][0] == 1 || grid[n - 1][n - 1] == 1)
        return 0;

    int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int total = n * n;
 
    int* dist_flat = malloc(total * sizeof(int));
    int* seen_flat = calloc(total, sizeof(int));

    memset(dist_flat, 127, total * sizeof(int)); // 0x7F7F... ≈ 1e9

    // Filas para BFS
    int* qr = malloc(total * sizeof(int));
    int* qc = malloc(total * sizeof(int));
    int front = 0, back = 0;
 
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1) {
                dist_flat[i * n + j] = 0;
                qr[back] = i;
                qc[back] = j;
                back++;
            }
        }
    }
 
    while (front < back) {
        int r = qr[front];
        int c = qc[front];
        front++;
        int curr_dist = dist_flat[r * n + c];

        for (int i = 0; i < 4; i++) {
            int nr = r + dirs[i][0];
            int nc = c + dirs[i][1];
            int idx = nr * n + nc;

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && 
                dist_flat[idx] > curr_dist + 1) {
                dist_flat[idx] = curr_dist + 1;
                qr[back] = nr;
                qc[back] = nc;
                back++;
            }
        }
    }
 
    MaxHeap* heap = createHeap(total + 1);
    push(heap, (Node){dist_flat[0], 0, 0});

    int result = -1;

    while (heap->size > 0) {
        Node cur = pop(heap);
        int safe = cur.safe;
        int r = cur.r;
        int c = cur.c;
        int idx = r * n + c;

        if (seen_flat[idx])
            continue;

        seen_flat[idx] = 1;
 
        if (r == n - 1 && c == n - 1) {
            result = safe;
            break;
        }

        int curr_dist = dist_flat[idx];

        for (int i = 0; i < 4; i++) {
            int nr = r + dirs[i][0];
            int nc = c + dirs[i][1];
            int nidx = nr * n + nc;

            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !seen_flat[nidx]) {
                int neighbor_dist = dist_flat[nidx];
                int newSafe = safe < neighbor_dist ? safe : neighbor_dist;
                push(heap, (Node){newSafe, nr, nc});
            }
        }
    }

    // Limpeza
    free(dist_flat);
    free(seen_flat);
    free(qr);
    free(qc);
    freeHeap(heap);

    return result;
}