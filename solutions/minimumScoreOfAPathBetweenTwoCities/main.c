#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<string.h>

typedef struct Node {
    int v;
    int w;
    struct Node* next;
} Node;

void addEdge(Node** adj, int u, int v, int w) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->v = v;
    newNode->w = w;
    newNode->next = adj[u];
    adj[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->v = u;
    newNode->w = w;
    newNode->next = adj[v];
    adj[v] = newNode;
}

int BFS(int n, Node** adj) {
    int ans = INT_MAX;
    bool* vis = (bool*)calloc(n + 1, sizeof(bool));
    int* queue = (int*)malloc((n + 1) * sizeof(int));
    int front = 0, rear = 0;
    
    queue[rear++] = 1;
    vis[1] = true;
    
    while (front < rear) {
        int u = queue[front++];
        Node* temp = adj[u];
        
        while (temp) {
            int v = temp->v;
            int wt = temp->w;
            
            if (wt == 1) {
                free(vis);
                free(queue);
                return 1;
            }
            
            if (wt < ans) ans = wt;
            
            if (!vis[v]) {
                vis[v] = true;
                queue[rear++] = v;
            }
            temp = temp->next;
        }
    }
    
    free(vis);
    free(queue);
    return ans;
}

int minScore(int n, int** roads, int roadsSize, int* roadsColSize) {
    Node** adj = (Node**)calloc(n + 1, sizeof(Node*));

    for (int i = 0; i < roadsSize; i++) {
        addEdge(adj, roads[i][0], roads[i][1], roads[i][2]);
    }
    
    int res = BFS(n, adj);
    
    for (int i = 1; i <= n; i++) {
        Node* temp = adj[i];
        while (temp) {
            Node* next = temp->next;
            free(temp);
            temp = next;
        }
    }
    free(adj);
    
    return res;
}