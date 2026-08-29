#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
    int value;
    int index;
} Pair;

typedef struct {
    int* indices;
    int size;
    int capacity;
} IndexGroup;

// Comparador seguro contra overflow
static inline int comparePair(const void* a, const void* b) {
    const Pair* p1 = (const Pair*)a;
    const Pair* p2 = (const Pair*)b;

    // Evitar overflow: usar comparação direta
    if (p1->value != p2->value) {
        return (p1->value > p2->value) - (p1->value < p2->value);
    }
    return p1->index - p2->index;
}

// Comparador para índices
static inline int compareInt(const void* a, const void* b) {
    return *(const int*)a - *(const int*)b;
}

/**
 * Otimização: Usar two-pointer com acumulação de índices
 * em vez de alocar array separado por grupo
 */
int* lexicographicallySmallestArray(int* nums, int numsSize, int limit, 
                                    int* returnSize) {
    // Validação
    if (!nums || numsSize <= 0 || !returnSize) {
        if (returnSize) *returnSize = 0;
        return NULL;
    }

    if (limit < 0) {
        if (returnSize) *returnSize = 0;
        return NULL;
    }

    int n = numsSize;

    // Alocação única para pares
    Pair* pairs = (Pair*)malloc(n * sizeof(Pair));
    if (!pairs) {
        *returnSize = 0;
        return NULL;
    }

    // Inicializar pares
    for (int i = 0; i < n; i++) {
        pairs[i].value = nums[i];
        pairs[i].index = i;
    }

    // Ordenar por valor (depois por índice)
    qsort(pairs, n, sizeof(Pair), comparePair);

    // Processar grupos: usar stack allocation para grupos pequenos
    // ou malloc para grupos grandes
    int* group_indices = NULL;
    int group_capacity = 0;

    int l = 0;
    while (l < n) {
        int r = l + 1;

        // Encontrar fim do grupo (diferença <= limit)
        while (r < n && pairs[r].value - pairs[r - 1].value <= limit) {
            r++;
        }

        int group_size = r - l;

        // Redimensionar se necessário
        if (group_size > group_capacity) {
            int* temp = (int*)realloc(group_indices, group_size * sizeof(int));
            if (!temp) {
                free(pairs);
                free(group_indices);
                *returnSize = 0;
                return NULL;
            }
            group_indices = temp;
            group_capacity = group_size;
        }

        // Coletar índices do grupo
        for (int i = 0; i < group_size; i++) {
            group_indices[i] = pairs[l + i].index;
        }

        // Ordenar índices (necessário para manter ordem original)
        qsort(group_indices, group_size, sizeof(int), compareInt);

        // Atribuir valores ordenados aos índices ordenados
        for (int i = 0; i < group_size; i++) {
            nums[group_indices[i]] = pairs[l + i].value;
        }

        l = r;
    }

    free(pairs);
    free(group_indices);

    *returnSize = n;
    return nums;
}