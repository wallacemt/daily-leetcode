#include <string.h>

int numDistinct(char* s, char* t) {
    int len1 = strlen(s), len2 = strlen(t);
    unsigned long long dp[len2 + 1];
     
    dp[0] = 1;
    for (int i = 1; i <= len2; i++) {
        dp[i] = 0;
    }

    for (int i = 0; i < len1; i++) {
        for (int j = len2 - 1; j >= 0; j--) {
            if (s[i] == t[j]) {
                dp[j + 1] += dp[j];
            }
        }
    }

    return (int)dp[len2];
}