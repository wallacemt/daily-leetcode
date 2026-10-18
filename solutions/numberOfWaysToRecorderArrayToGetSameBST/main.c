#include <stdio.h>
#include <stdlib.h>

#define MOD 1000000007LL

// Função para calcular combinações binomiais
void calculateCombinations(long long** comb, int n) {
    for (int i = 0; i <= n; i++) {
        comb[i][0] = comb[i][i] = 1; // C(i, 0) = C(i, i) = 1
        for (int j = 1; j < i; j++) {
            comb[i][j] = (comb[i - 1][j - 1] + comb[i - 1][j]) % MOD;
        }
    }
}

// Função recursiva para contar maneiras de construir a BST
long long countWays(int* arr, int n, long long** comb) {
    if (n <= 2) {
        return 1;
    }

    int root = arr[0];
    int* left = malloc(n * sizeof(int));
    int* right = malloc(n * sizeof(int));
    int L = 0, R = 0;

    // Divide os elementos em sub-arrays esquerdo e direito
    for (int i = 1; i < n; i++) {
        if (arr[i] < root) {
            left[L++] = arr[i];
        } else {
            right[R++] = arr[i];
        }
    }

    long long ways = comb[L + R][L]; // C(L + R, L)

    long long leftWays = countWays(left, L, comb);
    long long rightWays = countWays(right, R, comb);

    free(left);
    free(right);

    return (ways * leftWays % MOD * rightWays % MOD);
}

// Função principal para calcular o número de maneiras
int numOfWays(int* nums, int numsSize) {
    int n = numsSize;
    long long** comb = malloc((n + 1) * sizeof(long long*));

    for (int i = 0; i <= n; i++) {
        comb[i] = calloc(i + 1, sizeof(long long));
    }

    // Calcula combinações
    calculateCombinations(comb, n);

    long long result = (countWays(nums, n, comb) - 1 + MOD) % MOD;

    for (int i = 0; i <= n; i++) {
        free(comb[i]);
    }
    free(comb);

    return (int)result;
}
