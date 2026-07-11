typedef struct Node {
    int value;
    struct Node* next;
} Node;

void addEdge(Node** adj, int u, int v) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->value = v;
    node->next = adj[u];
    adj[u] = node;
}

bool bfs(int start, Node** adj, bool* visited, int n) {
    int* queue = (int*)malloc(n * sizeof(int));
    int front = 0;
    int back = 0;
    
    queue[back++] = start;
    visited[start] = true;
    
    int nodes = 0;
    int edgeCount = 0;
    
    while (front < back) {
        int curr = queue[front++];
        nodes++;
        
        for (Node* node = adj[curr]; node != NULL; node = node->next) {
            int nei = node->value;
            edgeCount++;
            
            if (!visited[nei]) {
                visited[nei] = true;
                queue[back++] = nei;
            }
        }
    }
    
    free(queue);
    
    int expectedEdges = nodes * (nodes - 1) / 2;
    bool isComplete = (edgeCount / 2) == expectedEdges;
    
    return isComplete;
}

int countCompleteComponents(int n, int** edges, int edgesSize, int* edgesColSize) {
    Node** adj = (Node**)calloc(n, sizeof(Node*));
    
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        addEdge(adj, u, v);
        addEdge(adj, v, u);
    }
    
    bool* visited = (bool*)calloc(n, sizeof(bool));
    int res = 0;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (bfs(i, adj, visited, n)) {
                res++;
            }
        }
    }
    
    for (int i = 0; i < n; i++) {
        Node* curr = adj[i];
        while (curr != NULL) {
            Node* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    
    free(adj);
    free(visited);
    
    return res;
}