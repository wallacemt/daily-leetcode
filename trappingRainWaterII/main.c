#include <stdlib.h>

typedef struct {
    int height;
    int row;
    int col;
} Cell;

typedef struct {
    Cell* data;
    int size;
    int capacity;
} MinHeap;

MinHeap* createHeap(int capacity) {
    MinHeap* heap = malloc(sizeof(MinHeap));
    heap->data = malloc(capacity * sizeof(Cell));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(Cell* a, Cell* b) {
    Cell temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MinHeap* heap, int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    if (heap->data[parent].height > heap->data[index].height) {
        swap(&heap->data[parent], &heap->data[index]);
        heapifyUp(heap, parent);
    }
}

void heapifyDown(MinHeap* heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;
    
    if (left < heap->size && heap->data[left].height < heap->data[smallest].height)
        smallest = left;
    if (right < heap->size && heap->data[right].height < heap->data[smallest].height)
        smallest = right;
        
    if (smallest != index) {
        swap(&heap->data[smallest], &heap->data[index]);
        heapifyDown(heap, smallest);
    }
}

void push(MinHeap* heap, int height, int row, int col) {
    heap->data[heap->size] = (Cell){height, row, col};
    heapifyUp(heap, heap->size);
    heap->size++;
}

Cell pop(MinHeap* heap) {
    Cell result = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    heapifyDown(heap, 0);
    return result;
}

int trapRainWater(int** heightMap, int heightMapSize, int* heightMapColSize) {
    if (heightMapSize <= 2 || heightMapColSize[0] <= 2) return 0;
    
    int m = heightMapSize;
    int n = heightMapColSize[0];
    int** visited = malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        visited[i] = calloc(n, sizeof(int));
    }
    
    MinHeap* heap = createHeap(m * n);
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || i == m-1 || j == 0 || j == n-1) {
                push(heap, heightMap[i][j], i, j);
                visited[i][j] = 1;
            }
        }
    }
    
    int directions[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
    int water = 0;
    
    while (heap->size > 0) {
        Cell current = pop(heap);
        
        for (int d = 0; d < 4; d++) {
            int newRow = current.row + directions[d][0];
            int newCol = current.col + directions[d][1];
            
            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && !visited[newRow][newCol]) {
                visited[newRow][newCol] = 1;
                int waterLevel = current.height > heightMap[newRow][newCol] ? 
                                current.height : heightMap[newRow][newCol];
                water += waterLevel - heightMap[newRow][newCol];
                push(heap, waterLevel, newRow, newCol);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        free(visited[i]);
    }
    free(visited);
    free(heap->data);
    free(heap);
    
    return water;
}