int peopleAwareOfSecret(int n, int delay, int forget) {
    int mod = 1000000007;
    long long dp[n + 1]; 
    
    for (int i = 0; i <= n; i++) {
        dp[i] = 0;
    }
    
    dp[1] = 1;  
    for (int i = 2; i <= n; i++) {
      
        for (int j = 1; j < i; j++) {
          
            if (i >= j + delay && i < j + forget) {
                dp[i] = (dp[i] + dp[j]) % mod;
            }
        }
    }
    
     long long result = 0;
    for (int i = 1; i <= n; i++) {
     
        if (n < i + forget) {
            result = (result + dp[i]) % mod;
        }
    }
    
    return result;
}
