#include <stdlib.h>
#include <string.h>

// Estrutura para lista de adjacência eficiente (Forward Star)
typedef struct {
    int head[100005];
    int next[100005];
    int to[100005];
    int edge_count;
} Graph;

void add_edge(Graph* g, int u, int v) {
    g->to[g->edge_count] = v;
    g->next[g->edge_count] = g->head[u];
    g->head[u] = g->edge_count++;
}

// DFS 1: Encontra os novos pais baseados nos caracteres
void find_new_parents(int u, Graph* g, char* s, int* char_ancestor, int* new_parent, int* old_parent) {
    int c = s[u] - 'a';
    int prev = char_ancestor[c];
    
    if (prev != -1) {
        new_parent[u] = prev;
    } else {
        new_parent[u] = old_parent[u];
    }
    
    int old_anc = char_ancestor[c];
    char_ancestor[c] = u;
    
    for (int i = g->head[u]; i != -1; i = g->next[i]) {
        find_new_parents(g->to[i], g, s, char_ancestor, new_parent, old_parent);
    }
    
    char_ancestor[c] = old_anc;
}

// DFS 2: Calcula o tamanho da subárvore na nova estrutura
int calculate_size(int u, Graph* g, int* subtree_size) {
    int sz = 1;
    for (int i = g->head[u]; i != -1; i = g->next[i]) {
        sz += calculate_size(g->to[i], g, subtree_size);
    }
    subtree_size[u] = sz;
    return sz;
}

int* findSubtreeSizes(int* parent, int parentSize, char* s, int* returnSize) {
    Graph* g = (Graph*)malloc(sizeof(Graph));
    int* new_parent = (int*)malloc(parentSize * sizeof(int));
    int* char_ancestor = (int*)malloc(26 * sizeof(int));
    int* subtree_size = (int*)malloc(parentSize * sizeof(int));
    
    // Construir árvore original
    g->edge_count = 0;
    memset(g->head, -1, sizeof(int) * parentSize);
    for (int i = 1; i < parentSize; i++) {
        add_edge(g, parent[i], i);
    }
     
    memset(char_ancestor, -1, sizeof(int) * 26);
    find_new_parents(0, g, s, char_ancestor, new_parent, parent);
     
    g->edge_count = 0;
    memset(g->head, -1, sizeof(int) * parentSize);
    for (int i = 1; i < parentSize; i++) {
        add_edge(g, new_parent[i], i);
    }
     
    calculate_size(0, g, subtree_size);
    
    *returnSize = parentSize;
    
    free(g);
    free(new_parent);
    free(char_ancestor);
    
    return subtree_size;
}