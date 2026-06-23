#include <stdlib.h>
#include <string.h>

int findMaxForm(char** strs, int strsSize, int m, int n) {
    if (m < 0 || n < 0 || strsSize <= 0) return 0;
    int cols = n + 1;
    int *dp = (int*)calloc((m + 1) * cols, sizeof(int));
    if (!dp) return 0;

    for (int s = 0; s < strsSize; ++s) {
        char *str = strs[s];
        int zeros = 0, ones = 0;
        for (int k = 0; str[k]; ++k) {
            if (str[k] == '0') ++zeros;
            else ++ones;
        }
        if (zeros > m || ones > n) continue;
        for (int i = m; i >= zeros; --i) {
            int base = i * cols;
            for (int j = n; j >= ones; --j) {
                int prev = dp[(i - zeros) * cols + (j - ones)] + 1;
                int cur = dp[base + j];
                if (prev > cur) dp[base + j] = prev;
            }
        }
    }

    int result = dp[m * cols + n];
    free(dp);
    return result;
}
