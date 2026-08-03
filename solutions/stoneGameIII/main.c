#include <limits.h>
#include <string.h>

char* stoneGameIII(int* stoneValue, int stoneValueSize) {
    int n = stoneValueSize;
    int dp[4];
    memset(dp, 0, sizeof(dp));
    
    // Pré-calcular sufixos para evitar recalcular takenScore
    int suffix[stoneValueSize + 1];
    suffix[n] = 0;
    
    for (int i = n - 1; i >= 0; i--) {
        suffix[i] = suffix[i + 1] + stoneValue[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        int bestDifference = INT_MIN;
        int idx = i % 4;
        
        // Desrolar o loop: tomar 1, 2 ou 3 pedras
        // Tomar 1 pedra
        int diff1 = stoneValue[i] - dp[(i + 1) % 4];
        if (diff1 > bestDifference) bestDifference = diff1;
        
        // Tomar 2 pedras
        if (i + 1 < n) {
            int diff2 = (stoneValue[i] + stoneValue[i + 1]) - dp[(i + 2) % 4];
            if (diff2 > bestDifference) bestDifference = diff2;
        }
         
        if (i + 2 < n) {
            int diff3 = (stoneValue[i] + stoneValue[i + 1] + stoneValue[i + 2]) - dp[(i + 3) % 4];
            if (diff3 > bestDifference) bestDifference = diff3;
        }

        dp[idx] = bestDifference;
    }

    int result = dp[0];
    
    if (result > 0) return "Alice";
    if (result < 0) return "Bob";
    return "Tie";
}