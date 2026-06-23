#define MOD 1000000007

int zigZagArrays(int n, int l, int r) {
    int m = r - l + 1;
    if (m == 1) return 2;
    
    long long* dp = malloc(m * sizeof(long long));
    long long* newDp = malloc(m * sizeof(long long));
    
    for (int i = 0; i < m; i++) {
        dp[i] = 1;
    }
    
    for (int i = 2; i <= n; i++) {
        long long prefixSum = 0;
        long long totalSum = 0;
        
        if (i % 2 == 0) {
            for (int j = 0; j < m; j++) {
                totalSum = (totalSum + dp[j]) % MOD;
            }
        } else {
            for (int j = 0; j < m; j++) {
                totalSum = (totalSum + dp[j]) % MOD;
            }
        }
        if (i % 2 == 0) {
      
            newDp[0] = 0;
            for (int j = 1; j < m; j++) {
                prefixSum = (prefixSum + dp[j - 1]) % MOD;
                newDp[j] = prefixSum;
            }
        } else {

            long long suffixSum = 0;
            for (int j = m - 1; j >= 0; j--) {
                newDp[j] = suffixSum;
                suffixSum = (suffixSum + dp[j]) % MOD;
            }
        }
        
        long long* temp = dp;
        dp = newDp;
        newDp = temp;
    }
    
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        ans = (ans + dp[i]) % MOD;
    }
    
    free(dp);
    free(newDp);
    
    return (ans * 2) % MOD;
}