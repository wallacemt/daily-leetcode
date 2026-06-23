void radixSort(int* nums, int numsSize)
{
    int* temp = (int*)malloc(numsSize * sizeof(int));
    int maxNum = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }
    
    for (long exp = 1; maxNum / exp > 0; exp *= 10) {
        int count[10] = {0};
        
        for (int i = 0; i < numsSize; i++) {
            count[(nums[i] / exp) % 10]++;
        }
        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }
        
        for (int i = numsSize - 1; i >= 0; i--) {
            int digit = (nums[i] / exp) % 10;
            temp[count[digit] - 1] = nums[i];
            count[digit]--;
        }
        
        for (int i = 0; i < numsSize; i++) {
            nums[i] = temp[i];
        }
    }
    
    free(temp);
}

int minRemoval(int* nums, int numsSize, int k)
{
    if (numsSize <= 1) return 0;
    
    radixSort(nums, numsSize);
    
    int maxLen = 1;
    int left = 0;
    
    for (int right = 1; right < numsSize; right++) {
        while (left < right && nums[right] > (long)nums[left] * k) {
            left++;
        }
        
        int len = right - left + 1;
        if (len > maxLen) {
            maxLen = len;
        }
    }
    
    return numsSize - maxLen;
}