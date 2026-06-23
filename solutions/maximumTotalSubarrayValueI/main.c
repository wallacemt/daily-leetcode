long long maxTotalValue(int* nums, int numsSize, int k) {
    int mn = nums[0], mx = nums[0];
    
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < mn)
            mn = nums[i];
        else if (nums[i] > mx)  
            mx = nums[i];
    }
    
    return 1LL * (mx - mn) * k;
}
