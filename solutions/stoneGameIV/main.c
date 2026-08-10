 
bool winnerSquareGame(int n) { 
    bool dp[n + 1];
    memset(dp, false, sizeof(dp));
     
    dp[0] = true;
    
    for (int i = 1; i <= n; i++) { 
        for (int j = 1; j * j <= i; j++) {
            if (dp[i - j * j]) {
                dp[i] = false;
                break;
            }
            dp[i] = true;
        }
    }
    
    return !dp[n];
}