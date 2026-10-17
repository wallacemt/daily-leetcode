#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int value;
    int digitSum;
    int originalIndex;
} Item;

// Função para calcular a soma dos dígitos
int digitSum(int n) {
    int sum = 0;
    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }
    return sum;
}

// Função de comparação para ordenação
int compare(const void* a, const void* b) {
    Item* itemA = (Item*)a;
    Item* itemB = (Item*)b;
    
    if (itemA->digitSum == itemB->digitSum) {
        return itemA->value - itemB->value; // Ordena pelo valor se as somas forem iguais
    }
    return itemA->digitSum - itemB->digitSum; // Ordena pela soma dos dígitos
}

// Função para calcular o número mínimo de trocas
int minSwaps(int* nums, int numsSize) {
    Item* items = malloc(numsSize * sizeof(Item));

    // Preenche os itens com valores, somas dos dígitos e índices
    for (int i = 0; i < numsSize; i++) {
        items[i].value = nums[i];
        items[i].digitSum = digitSum(nums[i]);
        items[i].originalIndex = i;
    }

    // Ordena os itens com base na soma dos dígitos
    qsort(items, numsSize, sizeof(Item), compare);

    // Contagem de ciclos para calcular trocas
    bool* visited = calloc(numsSize, sizeof(bool));
    int swaps = 0;

    for (int i = 0; i < numsSize; i++) {
        if (visited[i] || items[i].originalIndex == i) {
            continue; // Já visitado ou já na posição correta
        }

        int cycleSize = 0;
        int j = i;

        while (!visited[j]) {
            visited[j] = true;
            j = items[j].originalIndex; // Segue o ciclo
            cycleSize++;
        }

        if (cycleSize > 1) {
            swaps += cycleSize - 1; // Para um ciclo de tamanho `n`, precisamos de `n-1` trocas
        }
    }

    free(items);
    free(visited);

    return swaps;
}
 
