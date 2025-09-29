#include <string.h>
#include <limits.h>

int minScoreTriangulation(int* values, int valuesSize) {
    int n = valuesSize;
    static int dp[51][51];
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = 0;
        }
    }
    
    for (int len = 3; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            dp[i][j] = INT_MAX;
            
            for (int k = i + 1; k < j; k++) {
                int cost = dp[i][k] + dp[k][j] + values[i] * values[j] * values[k];
                if (cost < dp[i][j]) {
                    dp[i][j] = cost;
                }
            }
        }
    }
    
    return dp[0][n - 1];
}
