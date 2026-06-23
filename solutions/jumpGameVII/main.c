#include <string.h>
#include <stdbool.h>

bool canReach(char* s, int minJump, int maxJump) {
    int n = strlen(s);
    
    if (s[n - 1] == '1') return false;
    
    if (n - 1 < minJump) return false;

    bool* dp = (bool*)malloc(n * sizeof(bool));
    memset(dp, 0, n * sizeof(bool));
    dp[0] = true;

    int reachable = 0;

    for (int i = 1; i < n; i++) {
        if (i >= minJump && dp[i - minJump]) 
            reachable++;

        if (i > maxJump && dp[i - maxJump - 1]) 
            reachable--;

        if (reachable > 0 && s[i] == '0')
            dp[i] = true;
    }

    bool result = dp[n - 1];
    free(dp);
    return result;
}
