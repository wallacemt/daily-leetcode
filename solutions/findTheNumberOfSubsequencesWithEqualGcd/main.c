#define MOD 1000000007

int getGcd(int a, int b) {
    while (b != 0) {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int subsequencePairCount(int* nums, int numsSize) {
    // Encontrar máximo
    int m = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > m) {
            m = nums[i];
        }
    }

    int size = m + 1;

    // Alocação contígua única (melhor cache locality)
    int* dpFlat = calloc(size * size, sizeof(int));
    int* newDpFlat = calloc(size * size, sizeof(int));
    
    dpFlat[0] = 1; // dp[0][0] = 1

    #define DP(g1, g2) dpFlat[(g1) * size + (g2)]
    #define NEW_DP(g1, g2) newDpFlat[(g1) * size + (g2)]

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];

        // Limpar apenas estados necessários (otimização crítica)
        memset(newDpFlat, 0, size * size * sizeof(int));

        for (int g1 = 0; g1 <= m; g1++) {
            int nextGcd1 = getGcd(g1, num);

            for (int g2 = 0; g2 <= m; g2++) {
                int ways = DP(g1, g2);

                if (ways == 0) {
                    continue;
                }

                int nextGcd2 = getGcd(g2, num);

                // Três transições
                NEW_DP(g1, g2) = (NEW_DP(g1, g2) + ways) % MOD;
                NEW_DP(nextGcd1, g2) = (NEW_DP(nextGcd1, g2) + ways) % MOD;
                NEW_DP(g1, nextGcd2) = (NEW_DP(g1, nextGcd2) + ways) % MOD;
            }
        }

        // Swap de ponteiros
        int* temp = dpFlat;
        dpFlat = newDpFlat;
        newDpFlat = temp;
    }

    // Contar resultado
    int ans = 0;
    for (int g = 1; g <= m; g++) {
        ans = (ans + DP(g, g)) % MOD;
    }

    free(dpFlat);
    free(newDpFlat);

    return ans;
}