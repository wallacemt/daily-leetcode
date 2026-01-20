int* minBitwiseArray(int* nums, int numsSize, int* returnSize) {
    int* ans = (int*)malloc(numsSize * sizeof(int));
    
    for(int i = 0; i < numsSize; i++) {
        int n = nums[i];
        if(n == 2) {
            ans[i] = -1;
        } else {
            int lsb = (n + 1) & (-(n + 1));
            ans[i] = n - (lsb >> 1);
        }
    }
    
    *returnSize = numsSize;
    return ans;
  }