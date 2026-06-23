#include <stdio.h>
#include <string.h>

#define MAXN 105

typedef long long ll;

#define MAX(a, b) ((a) > (b) ? (a) : (b))

long long maximumScore(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    if (n == 1) return 0;

    ll colSum[MAXN][MAXN];
    memset(colSum, 0, sizeof(colSum));
    
    for (int c = 0; c < n; c++) {
        for (int r = 1; r <= n; r++) {
            colSum[c][r] = colSum[c][r - 1] + grid[r - 1][c];
        }
    }

    static ll dp[MAXN][MAXN][MAXN];
    static ll prevMax[MAXN][MAXN];
    static ll prevSuffixMax[MAXN][MAXN];
    
    memset(dp, 0, sizeof(dp));
    memset(prevMax, 0, sizeof(prevMax));
    memset(prevSuffixMax, 0, sizeof(prevSuffixMax));

    // Processar cada coluna
    for (int i = 1; i < n; i++) {
        for (int currH = 0; currH <= n; currH++) {
            for (int prevH = 0; prevH <= n; prevH++) {
                ll best;
                
                if (currH <= prevH) {
                    // Caso 1: altura atual <= altura anterior
                    ll extraScore = colSum[i][prevH] - colSum[i][currH];
                    best = prevSuffixMax[prevH][0] + extraScore;
                } else {
                    // Caso 2: altura atual > altura anterior
                    ll extraScore = colSum[i - 1][currH] - colSum[i - 1][prevH];
                    ll candidate1 = prevSuffixMax[prevH][currH];
                    ll candidate2 = prevMax[prevH][currH] + extraScore;
                    best = MAX(candidate1, candidate2);
                }
                
                dp[i][currH][prevH] = best;
            }
        }

        for (int currH = 0; currH <= n; currH++) {
            prevMax[currH][0] = dp[i][currH][0];
            
            for (int prevH = 1; prevH <= n; prevH++) {
                ll penalty = (prevH > currH) ? 
                    (colSum[i][prevH] - colSum[i][currH]) : 0;
                ll val = dp[i][currH][prevH] - penalty;
                prevMax[currH][prevH] = MAX(prevMax[currH][prevH - 1], val);
            }

            prevSuffixMax[currH][n] = dp[i][currH][n];
            
            for (int prevH = n - 1; prevH >= 0; prevH--) {
                prevSuffixMax[currH][prevH] = 
                    MAX(prevSuffixMax[currH][prevH + 1], dp[i][currH][prevH]);
            }
        }
    }

    ll ans = 0;
    for (int k = 0; k <= n; k++) {
        ans = MAX(ans, MAX(dp[n - 1][n][k], dp[n - 1][0][k]));
    }

    return ans;
}