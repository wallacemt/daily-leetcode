int* leftRightDifference(int* nums, int numsSize, int* returnSize) {
    
    
    int total = 0;
    for (int i = 0; i < numsSize; i++) {
        total += nums[i];
    }
    
    int* res = malloc(sizeof(int) * numsSize);
    
    int leftSum = 0;
    for (int i = 0; i < numsSize; i++) {
        int rightSum = total - leftSum - nums[i];
        
        int diff = leftSum - rightSum;
        res[i] = (diff < 0) ? -diff : diff;
        
        leftSum += nums[i];
    }
    
    *returnSize = numsSize;
    return res;
}