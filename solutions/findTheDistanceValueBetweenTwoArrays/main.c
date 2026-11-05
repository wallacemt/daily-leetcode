#include <stdio.h>
#include <stdlib.h>

// Função de comparação para qsort
int cmpInts(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}
 
int findTheDistanceValue(int* arr1, int arr1Size, int* arr2, int arr2Size, int d) {
    // Ordenar arr2 para permitir busca binária
    qsort(arr2, arr2Size, sizeof(int), cmpInts);
    int count = arr1Size;

    for (int i = 0; i < arr1Size; i++) {
        // Calcular os limites inferior e superior
        int lowerBound = arr1[i] - d;
        int upperBound = arr1[i] + d;

        // Usar busca binária para encontrar a posição
        int left = 0, right = arr2Size - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr2[mid] < lowerBound) {
                left = mid + 1; // Mover para a direita
            } else if (arr2[mid] > upperBound) {
                right = mid - 1; // Mover para a esquerda
            } else {
                // Encontrou um elemento em arr2 que está dentro do intervalo
                count--;
                break;
            }
        }
    }

    return count;
}
 