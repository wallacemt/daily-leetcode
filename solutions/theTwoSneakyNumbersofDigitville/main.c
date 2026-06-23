int* getSneakyNumbers(int* nums, int numsSize, int* returnSize) {
    *returnSize = 2;
    int* result = (int*)malloc(2 * sizeof(int));
    
    int freq[100] = {0};
    int index = 0;
    
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
        if (freq[nums[i]] == 2) {
            result[index++] = nums[i];
            if (index == 2) {
                break;
            }
        }
    }
    
    return result;
}
