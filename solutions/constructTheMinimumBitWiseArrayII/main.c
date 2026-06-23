int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    for(int i = 0; i < numsSize; i++) {
        int n = nums[i];
        ans[i] = (n == 2) ? -1 : n - (((n + 1) & (-n - 1)) >> 1);
    }
    
    *returnSize = numsSize;
    return ans;
}
