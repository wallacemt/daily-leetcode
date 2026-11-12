int longestMonotonicSubarray(int* nums, int numsSize) {
    if (numsSize <= 0) return 0;
    if (numsSize == 1) return 1;

    int maxLen = 1;
    int inc = 1; // Contador para crescente
    int dec = 1; // Contador para decrescente

    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i + 1] > nums[i]) {
            inc++;
            dec = 1; // Reseta o decrescente
        } else if (nums[i + 1] < nums[i]) {
            dec++;
            inc = 1; // Reseta o crescente
        } else {
            // Se forem iguais, ambos resetam para 1
            inc = 1;
            dec = 1;
        }

        // Atualiza o máximo global
        if (inc > maxLen) maxLen = inc;
        if (dec > maxLen) maxLen = dec;
    }

    return maxLen;
}