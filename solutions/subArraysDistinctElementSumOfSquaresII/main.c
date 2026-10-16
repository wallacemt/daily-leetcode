#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007LL
 
long long prefix_sum(int k, long long* bit1, long long* bit2) {
    long long s1 = 0, s2 = 0;
    int index = k;

    while (index > 0) {
        s1 += bit1[index];
        s2 += bit2[index];
        index -= index & -index; // Desloca para o pai
    }

    return (long long)k * s1 - s2;
}
 
void add_boundary(int index, long long delta, int n, long long* bit1, long long* bit2) {
    long long weighted = delta * (index - 1);

    while (index <= n) {
        bit1[index] += delta;
        bit2[index] += weighted;
        index += index & -index; // Desloca para o pai
    }
}
 
int sumCounts(int* nums, int numsSize) {
    int n = numsSize;

    long long* bit1 = calloc(n + 1, sizeof(long long));
    long long* bit2 = calloc(n + 1, sizeof(long long));
    int* last = malloc(100001 * sizeof(int));

    // Inicializa o vetor 'last' com -1
    for (int i = 0; i <= 100000; i++) {
        last[i] = -1;
    }

    long long total_distinct = 0; // Total de elementos distintos
    long long ending_squares = 0; // Soma dos quadrados das contagens
    long long answer = 0; // Resposta total

    // Itera sobre todos os elementos do array
    for (int i = 0; i < n; i++) {
        int value = nums[i];
        int p = last[value]; // Última posição do valor

        // Calcula a soma afetada
        long long affected_sum = total_distinct - prefix_sum(p + 1, bit1, bit2);
        long long length = i - p; // Comprimento do subarray

        // Atualiza a soma dos quadrados das contagens
        ending_squares = (ending_squares + 2 * affected_sum + length) % MOD;
        answer = (answer + ending_squares) % MOD;

        // Adiciona limites na árvore de Fenwick
        add_boundary(p + 2, 1, n, bit1, bit2);
        add_boundary(i + 2, -1, n, bit1, bit2);

        total_distinct += length; // Atualiza total de distintos
        last[value] = i; // Atualiza a última posição do valor
    }

    free(bit1);
    free(bit2);
    free(last);

    return (int)answer;
}