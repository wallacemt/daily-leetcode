#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define INF 2147483647  
#define ALPHABET_SIZE 27

int dist(int a, int b) {
    if (a == 26 || b == 26) 
        return 0;
    return abs(a / 6 - b / 6) + abs(a % 6 - b % 6);
}

int minimumDistance(char * word) {
    if (!word || *word == '\0') 
        return 0;
    
    int n = strlen(word);
    int dp[ALPHABET_SIZE];
    int next_dp[ALPHABET_SIZE];
    
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        dp[i] = INF;
    dp[26] = 0;  
    
    int prev = word[0] - 'A';

    // Processamento de cada caractere
    for (int i = 1; i < n; i++) {
        int cur = word[i] - 'A';
        
        for (int j = 0; j < ALPHABET_SIZE; j++) 
            next_dp[j] = INF;
        
        for (int free = 0; free < ALPHABET_SIZE; free++) {
            if (dp[free] >= INF) 
                continue;
            
            int d1 = dp[free] + dist(prev, cur);
            if (d1 < next_dp[free]) 
                next_dp[free] = d1;
            
            int d2 = dp[free] + dist(free, cur);
            if (d2 < next_dp[prev]) 
                next_dp[prev] = d2;
        }
        
        for (int j = 0; j < ALPHABET_SIZE; j++) 
            dp[j] = next_dp[j];
        
        prev = cur;
    }

    int res = INF;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (dp[i] < res) 
            res = dp[i];
    }
    
    return res == INF ? 0 : res;
}