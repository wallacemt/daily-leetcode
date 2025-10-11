#include <stdio.h>
#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

long long maximumTotalDamage(int* power, int powerSize) {
    qsort(power, powerSize, sizeof(int), compare);
    int unique[100000];
    long long freq[100000];
    int uniqueCount = 0;
    
    int i = 0;
    while (i < powerSize) {
        unique[uniqueCount] = power[i];
        freq[uniqueCount] = 0;
        
        while (i < powerSize && power[i] == unique[uniqueCount]) {
            freq[uniqueCount] += power[i];
            i++;
        }
        uniqueCount++;
    }
    
    long long dp[100000];
    dp[0] = freq[0];
    
    if (uniqueCount == 1) return dp[0];
    
    dp[1] = (unique[1] - unique[0] <= 2) ? 
            (freq[0] > freq[1] ? freq[0] : freq[1]) : 
            freq[0] + freq[1];
    
    for (i = 2; i < uniqueCount; i++) {
        dp[i] = dp[i-1];
        
        if (unique[i] - unique[i-1] > 2) {
            long long take = dp[i-1] + freq[i];
            if (take > dp[i]) dp[i] = take;
        } else if (unique[i] - unique[i-2] > 2) {
            long long take = dp[i-2] + freq[i];
            if (take > dp[i]) dp[i] = take;
        } else {
            long long take = freq[i];
            if (i >= 3) take += dp[i-3];
            if (take > dp[i]) dp[i] = take;
        }
    }
    
    return dp[uniqueCount-1];
}