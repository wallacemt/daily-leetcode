#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXN 201
#define INF 1e7

int factors[MAXN][MAXN];
int factorSizes[MAXN];
int initialized = 0;

void initFactors() {
    if (initialized) return;
    for (int i = 1; i < MAXN; i++) {
        factorSizes[i] = 0;
        for (int j = 1; j <= i / 2; j++) {
            if (i % j == 0) {
                factors[i][factorSizes[i]++] = j;
            }
        }
    }
    initialized = 1;
}
 
int get_cost(char* s, int left, int right, int d) {
    int cnt = 0;
    int len = right - left + 1;
    int num_groups = d;
    int group_size = len / d;
    
    for (int g = 0; g < num_groups; g++) {
        int l = 0;
        int r = group_size - 1;
        while (l < r) {
            if (s[left + g + l * num_groups] != s[left + g + r * num_groups]) {
                cnt++;
            }
            l++;
            r--;
        }
    }
    return cnt;
}

int countChanges(char* s, int l, int r) {
    int len = r - l + 1;
    int minChanges = len;
    for (int k = 0; k < factorSizes[len]; k++) {
        int d = factors[len][k];
        int cost = get_cost(s, l, r, d);
        if (cost < minChanges) minChanges = cost;
    }
    return minChanges;
}

int minimumChanges(char* s, int k) {
    initFactors();
    int n = strlen(s);

    // sub[i][j] armazena o custo para a substring s[i...j]
    int sub[MAXN][MAXN];
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            sub[i][j] = countChanges(s, i, j);
        }
    }
 
    int dp[MAXN][MAXN];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= n; j++) dp[i][j] = INF;
    }

    dp[0][0] = 0;

    for (int kk = 1; kk <= k; kk++) {
        for (int j = kk * 2; j <= n; j++) {  
            for (int i = (kk - 1) * 2; i <= j - 2; i++) {
                int current_cost = dp[kk - 1][i] + sub[i][j - 1];
                if (current_cost < dp[kk][j]) {
                    dp[kk][j] = current_cost;
                }
            }
        }
    }

    return dp[k][n];
}