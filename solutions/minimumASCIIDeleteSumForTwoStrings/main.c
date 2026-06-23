#include <string.h>
#include <stdlib.h>

int minimumDeleteSum(char* s1, char* s2) {
    int n = strlen(s1);
    int m = strlen(s2);

    int sum1 = 0, sum2 = 0;
    for (int i = 0; i < n; i++) sum1 += s1[i];
    for (int i = 0; i < m; i++) sum2 += s2[i];
    int total = sum1 + sum2;

    int* dp = (int*)calloc(m + 1, sizeof(int));

    for (int i = 0; i < n; i++) {
        int prev = 0; 
        for (int j = 0; j < m; j++) {
            int curr = dp[j + 1];  
            
            if (s1[i] == s2[j]) {
                dp[j + 1] = prev + (int)s1[i];
            } else {
                dp[j + 1] = (dp[j + 1] > dp[j]) ? dp[j + 1] : dp[j];
            }
            prev = curr;
        }
    }

    int ans = total - 2 * dp[m];
    free(dp);

    return ans;
}