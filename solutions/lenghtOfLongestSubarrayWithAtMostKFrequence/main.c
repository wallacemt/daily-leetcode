#include <string.h>
#include <stdlib.h>

int maxSubarrayLength(int* nums, int numsSize, int k) {
    // Assumindo valores positivos razoáveis
    // Aloca map dinâmico baseado no máximo valor
    int maxVal = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }

    // Array direto: O(1) acesso garantido
    int* count = (int*)calloc(maxVal + 1, sizeof(int));

    int left = 0;
    int res = 0;

    for (int right = 0; right < numsSize; right++) {
        count[nums[right]]++;

        // Contrai janela enquanto houver violação
        while (count[nums[right]] > k) {
            count[nums[left]]--;
            left++;
        }

        int length = right - left + 1;
        if (length > res) {
            res = length;
        }
    }

    free(count);
    return res;
}