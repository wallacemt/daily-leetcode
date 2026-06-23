#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_NODES 210
#define ALPHABET_SIZE 26
#define INF 1000000000000000LL

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    int id;
} TrieNode;

TrieNode* create() {
    TrieNode* node = malloc(sizeof(TrieNode));
    node->id = -1;
    memset(node->children, 0, sizeof(node->children));
    return node;
}

int insert(TrieNode* root, const char* str, int* next) {
    TrieNode* curr = root;
    for (int i = 0; str[i]; i++) {
        int idx = str[i] - 'a';
        if (!curr->children[idx])
            curr->children[idx] = create();
        curr = curr->children[idx];
    }
    if (curr->id == -1)
        curr->id = (*next)++;
    return curr->id;
}

int search(TrieNode* root, const char* str, int start, int len) {
    TrieNode* curr = root;
    for (int i = 0; i < len; i++) {
        int idx = str[start + i] - 'a';
        if (!curr->children[idx])
            return -1;
        curr = curr->children[idx];
    }
    return curr->id;
}

void freeTrieNode(TrieNode* node) {
    if (!node) return;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        freeTrieNode(node->children[i]);
    free(node);
}

long long minimumCost(char* src, char* tar, char** orig, int origSize,
                      char** chg, int chgSize, int* cost, int costSize) {
    int n = strlen(src);
    TrieNode* root = create();
    int next = 0;

    int lens[105], lenCnt = 0;
    int lenEx[1005] = {0};

    for (int i = 0; i < origSize; i++) {
        insert(root, orig[i], &next);
        int len = strlen(orig[i]);
        if (!lenEx[len]) {
            lens[lenCnt++] = len;
            lenEx[len] = 1;
        }
    }

    for (int i = 0; i < chgSize; i++)
        insert(root, chg[i], &next);

    int num = next;
    long long** dist = malloc(num * sizeof(long long*));
    for (int i = 0; i < num; i++) {
        dist[i] = malloc(num * sizeof(long long));
        for (int j = 0; j < num; j++)
            dist[i][j] = (i == j) ? 0 : INF;
    }

    for (int i = 0; i < costSize; i++) {
        int u = insert(root, orig[i], &next);
        int v = insert(root, chg[i], &next);
        if ((long long)cost[i] < dist[u][v])
            dist[u][v] = (long long)cost[i];
    }

    for (int k = 0; k < num; k++)
        for (int i = 0; i < num; i++)
            if (dist[i][k] < INF)
                for (int j = 0; j < num; j++)
                    if (dist[k][j] < INF && dist[i][k] + dist[k][j] < dist[i][j])
                        dist[i][j] = dist[i][k] + dist[k][j];

    long long* dp = malloc((n + 1) * sizeof(long long));
    for (int i = 0; i <= n; i++)
        dp[i] = INF;
    dp[n] = 0;

    for (int i = n - 1; i >= 0; i--) {
        if (src[i] == tar[i]) {
            dp[i] = dp[i + 1];
        }
        
        for (int k = 0; k < lenCnt; k++) {
            int len = lens[k];
            if (i + len <= n) {
                int u = search(root, src, i, len);
                int v = search(root, tar, i, len);
                if (u != -1 && v != -1 && dist[u][v] < INF && dp[i + len] < INF) {
                    long long newCost = dist[u][v] + dp[i + len];
                    if (newCost < dp[i])
                        dp[i] = newCost;
                }
            }
        }
    }

    long long res = (dp[0] < INF) ? dp[0] : -1;

    free(dp);
    for (int i = 0; i < num; i++)
        free(dist[i]);
    free(dist);
    freeTrieNode(root);

    return res;
}