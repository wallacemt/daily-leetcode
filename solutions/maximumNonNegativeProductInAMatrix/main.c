#include <stdlib.h>
#include <string.h>

int maxProductPath(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    const long long MOD = 1000000007;
    
    long long* max_dp = (long long*)malloc(n * sizeof(long long));
    long long* min_dp = (long long*)malloc(n * sizeof(long long));
    long long* max_temp = (long long*)malloc(n * sizeof(long long));
    long long* min_temp = (long long*)malloc(n * sizeof(long long));
    
    
    max_dp[0] = min_dp[0] = grid[0][0];
    for (int j = 1; j < n; ++j) {
        max_dp[j] = min_dp[j] = max_dp[j-1] * grid[0][j];
    }
    
    for (int i = 1; i < m; ++i) {
        long long val = grid[i][0];
        max_temp[0] = min_temp[0] = max_dp[0] * val;
        
        for (int j = 1; j < n; ++j) {
            val = grid[i][j];
            
            long long max_from_top = max_dp[j];
            long long max_from_left = max_temp[j-1];
            long long min_from_top = min_dp[j];
            long long min_from_left = min_temp[j-1];
            
            long long max_prev = (max_from_top > max_from_left) ? max_from_top : max_from_left;
            long long min_prev = (min_from_top < min_from_left) ? min_from_top : min_from_left;
            
            if (val < 0) {
                max_temp[j] = min_prev * val;
                min_temp[j] = max_prev * val;
            } else {
                max_temp[j] = max_prev * val;
                min_temp[j] = min_prev * val;
            }
        }
        
        long long* tmp = max_dp;
        max_dp = max_temp;
        max_temp = tmp;
        
        tmp = min_dp;
        min_dp = min_temp;
        min_temp = tmp;
    }
    
    long long ans = max_dp[n-1];
    
    // Liberação de memória
    free(max_dp);
    free(min_dp);
    free(max_temp);
    free(min_temp);
    
    if (ans < 0) {
        return -1;
    }
    
    ans = ans % MOD;
    if (ans < 0) ans += MOD;
    
    return (int)ans;
}