#define MOD 1000000007

typedef struct node {			
    int v;
    struct node* next;
} Node;
 
typedef struct adjList {        
    Node *head;
} AdjList;
 
typedef struct graph {          
    int numV;                   
    AdjList* list;              
} Graph;
 
Node* newAdjListNode(int v) {
    Node* newNode = calloc(1, sizeof(Node)); // ✅ Ordem correta
    newNode->v = v;
    return newNode;
}
 
Graph* createGraph(int v) {
    Graph* graph = calloc(1, sizeof(Graph)); // ✅ Ordem correta
    graph->list = calloc(v, sizeof(AdjList)); // ✅ Ordem correta
    graph->numV = v;
    return graph;
}
 
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = newAdjListNode(dest);
    newNode->next = graph->list[src].head;
    graph->list[src].head = newNode;
   
    newNode = newAdjListNode(src);
    newNode->next = graph->list[dest].head;
    graph->list[dest].head = newNode;
}

void freeGraph(Graph* g) {
    if (!g) return;
    for (int i = 0; i < g->numV; i++) {
        Node* current = g->list[i].head;
        while (current) {
            Node* temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(g->list);
    free(g);
}
int power(int a, int b) {
    long long result = 1;
    long long base = a;
    
    while (b) {
        if (b & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD; 
        b >>= 1; // Mais rápido que b /= 2
    }
    return (int)result;
}

int dfs(Graph *g, int x, int f, int* memo) {
    if (memo[x] != -1) {
        return memo[x];
    }
    
    int maxDepth = 0;
    Node *y = g->list[x].head;
    
    while (y) {
        if (y->v != f) {
            maxDepth = fmax(maxDepth, 1 + dfs(g, y->v, x, memo));
        }
        y = y->next;
    }
    
    memo[x] = maxDepth;
    return maxDepth;
}

int assignEdgeWeights(int** edges, int edgesSize, int* edgesColSize) {
    Graph *g = createGraph(edgesSize + 2);
    
    for (int e = 0; e < edgesSize; e++) {
        addEdge(g, edges[e][0], edges[e][1]);
    }
    
    int* memo = calloc(edgesSize + 2, sizeof(int));
    for (int i = 0; i < edgesSize + 2; i++) {
        memo[i] = -1;
    }
    
    int maxDepth = dfs(g, 1, 0, memo);
    int result = power(2, maxDepth - 1);
    
    free(memo);
    freeGraph(g);
    
    return result;
}