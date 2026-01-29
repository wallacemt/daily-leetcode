#include <string.h>
#include <limits.h>

long long minimumCost(char* source, char* target, char* original, int originalSize, char* changed, int changedSize, int* cost, int costSize) {
    const long long INF = 1e14;
    long long dist[26][26];

    for (int i = 0; i < 26; i++) {
        for (int j = 0; j < 26; j++) {
            dist[i][j] = INF;
        }
        dist[i][i] = 0;
    }
    for (int i = 0; i < originalSize; i++) {
        int u = original[i] - 'a';
        int v = changed[i] - 'a';
        long long c = (long long)cost[i];
        if (c < dist[u][v]) {
            dist[u][v] = c;
        }
    }

    for (int k = 0; k < 26; k++) {
        for (int i = 0; i < 26; i++) {
            long long dist_ik = dist[i][k];
            if (dist_ik >= INF) continue;
            
            for (int j = 0; j < 26; j++) {
                long long dist_kj = dist[k][j];
                if (dist_kj < INF) {
                    long long new_dist = dist_ik + dist_kj;
                    if (new_dist < dist[i][j]) {
                        dist[i][j] = new_dist;
                    }
                }
            }
        }
    }

    long long ans = 0;
    int len = strlen(source);
    
    for (int i = 0; i < len; i++) {
        if (source[i] != target[i]) {
            int u = source[i] - 'a';
            int v = target[i] - 'a';
            
            if (dist[u][v] >= INF) {
                return -1;
            }
            ans += dist[u][v];
        }
    }

    return ans;
}