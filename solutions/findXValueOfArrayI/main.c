#include <stdlib.h>
#include <string.h>
#include <limits.h>
 
long long* resultArray(int* nums, int numsSize, int k, int* returnSize) {
    // Validação de entrada
    if (!nums || !returnSize || numsSize <= 0 || k <= 0) {
        if (returnSize) {
            *returnSize = 0;
        }
        return NULL;
    }

    int n = numsSize;
    *returnSize = k;

    // Aloca resultado com verificação
    long long* ans = (long long*)calloc(k, sizeof(long long));
    if (!ans) {
        *returnSize = 0;
        return NULL;
    }

    // Caso especial: k == 1
    if (k == 1) {
        ans[0] = (long long)n * (n + 1) / 2;
        return ans;
    }

    // Aloca arrays de frequência com verificação
    long long* freq = (long long*)calloc(k, sizeof(long long));
    long long* freq2 = (long long*)calloc(k, sizeof(long long));

    if (!freq || !freq2) {
        free(ans);
        free(freq);
        free(freq2);
        *returnSize = 0;
        return NULL;
    }

    // Processa cada elemento
    for (int i = 0; i < n; i++) {
        int r = nums[i] % k;
        if (r < 0) {
            r += k;  // Garante resto positivo
        }

        // Limpa freq2 (otimizado: só limpa até k)
        memset(freq2, 0, k * sizeof(long long));

        // Incrementa para subarray de um elemento
        ans[r]++;

        // Processa combinações com elementos anteriores
        for (int j = 0; j < k; j++) {
            if (freq[j] > 0) {
                int prod = (j * r) % k;

                // Verifica overflow
                if (freq2[prod] > LLONG_MAX - freq[j]) {
                    free(ans);
                    free(freq);
                    free(freq2);
                    *returnSize = 0;
                    return NULL;
                }

                freq2[prod] += freq[j];

                // Verifica overflow
                if (ans[prod] > LLONG_MAX - freq[j]) {
                    free(ans);
                    free(freq);
                    free(freq2);
                    *returnSize = 0;
                    return NULL;
                }

                ans[prod] += freq[j];
            }
        }
 
        freq2[r]++;

        // Troca arrays
        long long* temp = freq;
        freq = freq2;
        freq2 = temp;
    }

    free(freq);
    free(freq2);

    return ans;
}