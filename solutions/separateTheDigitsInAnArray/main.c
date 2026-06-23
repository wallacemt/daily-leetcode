int* separateDigits(int* nums, int numsSize, int* returnSize) {
    int* res = (int*)malloc(sizeof(int) * numsSize * 10);
    int idx = 0;
    
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        
        if (num > 9) {
            // Contar dígitos
            int temp = num;
            int digitCount = 0;
            while (temp > 0) {
                digitCount++;
                temp /= 10;
            }
            
            int divisor = 1;
            for (int j = 1; j < digitCount; j++) {
                divisor *= 10;
            }
            
            while (divisor > 0) {
                res[idx++] = num / divisor;
                num %= divisor;
                divisor /= 10;
            }
        } 
        else {
            res[idx++] = num;
        }
    }
    
    *returnSize = idx;
    return res;
}
