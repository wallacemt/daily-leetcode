#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int binarySearch(int* potions, int potionsSize, long long target) {
    int left = 0, right = potionsSize - 1;
    int result = potionsSize;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (potions[mid] >= target) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    
    return result;
}

int* successfulPairs(int* spells, int spellsSize, int* potions, int potionsSize, long long success, int* returnSize) {
    int* result = (int*)malloc(spellsSize * sizeof(int));
    *returnSize = spellsSize;
    
    // Ordena o array potions
    qsort(potions, potionsSize, sizeof(int), compare);
    
    for (int i = 0; i < spellsSize; i++) {
        // Calcula o valor mínimo necessário da poção
        long long minPotion = (success + spells[i] - 1) / spells[i]; // ceiling division
        
        // Busca binária para encontrar a primeira poção >= minPotion
        int index = binarySearch(potions, potionsSize, minPotion);
        
        // Conta quantas poções são válidas
        result[i] = potionsSize - index;
    }
    
    return result;
}
