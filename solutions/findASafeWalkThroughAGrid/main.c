#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    int x, y, health;
} Node;

typedef struct {
    Node* queue;
    int front, rear;
    int capacity;
} Queue;

// Inicializa fila com capacidade dinâmica
Queue* queueCreate(int initialCapacity) {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->queue = (Node*)malloc(initialCapacity * sizeof(Node));
    q->front = 0;
    q->rear = 0;
    q->capacity = initialCapacity;
    return q;
}

// Redimensiona fila quando necessário
void queueResize(Queue* q) {
    int newCapacity = q->capacity * 2;
    Node* newQueue = (Node*)malloc(newCapacity * sizeof(Node));
    
    // Copia elementos existentes
    int count = 0;
    for (int i = q->front; i != q->rear; i = (i + 1) % q->capacity) {
        newQueue[count++] = q->queue[i];
    }
    
    free(q->queue);
    q->queue = newQueue;
    q->capacity = newCapacity;
    q->front = 0;
    q->rear = count;
}

static inline void enqueue(Queue* q, int x, int y, int health) {
    // Verifica se precisa redimensionar
    if ((q->rear + 1) % q->capacity == q->front) {
        queueResize(q);
    }
    
    q->queue[q->rear].x = x;
    q->queue[q->rear].y = y;
    q->queue[q->rear].health = health;
    q->rear = (q->rear + 1) % q->capacity;
}

static inline Node dequeue(Queue* q) {
    Node node = q->queue[q->front];
    q->front = (q->front + 1) % q->capacity;
    return node;
}

static inline int isEmpty(Queue* q) {
    return q->front == q->rear;
}

void queueFree(Queue* q) {
    free(q->queue);
    free(q);
}

bool findSafeWalk(int** grid, int gridSize, int* gridColSize, int health) {
    int directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    
    int m = gridSize;
    int n = gridColSize[0];
    
    int initialHealth = health - grid[0][0];
    if (initialHealth < 1) return false;
    
    // Cria fila com capacidade inicial
    Queue* queue = queueCreate(1024);
    enqueue(queue, 0, 0, initialHealth);
    
    // Alocação contígua em memória
    int* visited_data = (int*)calloc(m * n, sizeof(int));
    if (!visited_data) {
        queueFree(queue);
        return false;
    }
    
    int** visited = (int**)malloc(m * sizeof(int*));
    if (!visited) {
        free(visited_data);
        queueFree(queue);
        return false;
    }
    
    for (int i = 0; i < m; i++) {
        visited[i] = visited_data + i * n;
    }
    
    visited[0][0] = initialHealth;

    bool result = false;
    
    while (!isEmpty(queue)) {
        Node current = dequeue(queue);
        int x = current.x;
        int y = current.y;
        int currentHealth = current.health;

        // Verificação antecipada
        if (x == m - 1 && y == n - 1) {
            result = true;
            break;
        }
 
        for (int i = 0; i < 4; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];
 
            if (newX >= 0 && newX < m && newY >= 0 && newY < n) {
                int newHealth = currentHealth - grid[newX][newY];
                 
                if (newHealth > 0 && newHealth > visited[newX][newY]) {
                    visited[newX][newY] = newHealth;
                    enqueue(queue, newX, newY, newHealth);
                }
            }
        }
    }
    
    free(visited);
    free(visited_data);
    queueFree(queue);

    return result;
}