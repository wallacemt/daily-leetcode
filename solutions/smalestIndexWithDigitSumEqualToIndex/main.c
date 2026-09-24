#include <limits.h>

#define NO_SOLUTION -1
#define RADIX 10
 
static int calcDigitSum(int num) {
    // Trata números negativos
    if (num < 0) {
        num = -num;
    }

    int sum = 0;

    // Caso especial: 0
    if (num == 0) {
        return 0;
    }

    // Calcula soma dos dígitos
    while (num > 0) {
        sum += num % RADIX;
        num /= RADIX;
    }

    return sum;
} 
int smallestIndex(int* nums, int numsSize) {
    // Validação de entrada
    if (!nums || numsSize <= 0) {
        return NO_SOLUTION;
    }

    // Procura o menor índice
    for (int i = 0; i < numsSize; ++i) {
        int digitSum = calcDigitSum(nums[i]);

        // Verifica se índice == soma dos dígitos
        if (i == digitSum) {
            return i;
        }
    }

    return NO_SOLUTION;
}