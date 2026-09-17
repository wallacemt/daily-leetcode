#include <stdlib.h>
#include <limits.h>

int minSumOfLengths(int* arr, int arrSize, int target) {
    // Validação de entrada
    if (!arr || arrSize <= 0 || target < 0) {
        return -1;
    }

    int n = arrSize;
    const int INF = n + 1;  // Valor "infinito" seguro
    int res = INF;
    int total = 0;
    int i = 0;

    // dp[j] = comprimento mínimo de subarray com soma=target até índice j-1
    int* dp = (int*)malloc((n + 1) * sizeof(int));
    if (!dp) {
        return -1;
    }

    // Inicializa com INF
    for (int j = 0; j <= n; j++) {
        dp[j] = INF;
    }

    // Sliding window
    for (int j = 0; j < n; j++) {
        total += arr[j];
 
        while (total > target) {
            total -= arr[i];
            i++;
        }
 
        dp[j + 1] = dp[j];
 
        if (total == target) {
            int len = j - i + 1;
 
            if (dp[i] != INF) {
                int candidate = len + dp[i];
                if (candidate < res) {
                    res = candidate;
                }
            }
 
            if (len < dp[j + 1]) {
                dp[j + 1] = len;
            }
        }
    }

    free(dp);

    return res == INF ? -1 : res;
}