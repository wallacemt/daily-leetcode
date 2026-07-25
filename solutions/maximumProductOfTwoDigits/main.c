#include <limits.h>

int maxProduct(int n) {
    // Validação de entrada
    if (n < 10) return 0;
    
    int arr[10], i = 0;
    
    // Extração de dígitos (mantém lógica original)
    while (n != 0) {
        arr[i++] = n % 10;
        n /= 10;
    }
    
    // Bubble Sort otimizado - O(n) no melhor caso
    int swapped;
    for (int j = 0; j < i - 1; j++) {
        swapped = 0;
        for (int k = 0; k < i - 1 - j; k++) {  // Reduz comparações
            if (arr[k] < arr[k + 1]) {
                int temp = arr[k];
                arr[k] = arr[k + 1];
                arr[k + 1] = temp;
                swapped = 1;
            }
        }
        if (!swapped) break;  // Sai se já está ordenado
    }
    
    return arr[0] * arr[1];
}