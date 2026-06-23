int compare(const void* a, const void* b) {
    int diff = *(int*)a - *(int*)b;
    return (diff > 0) - (diff < 0);  
}

int minimumDifference(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), compare);
    
    int ans = INT_MAX;
    int end = numsSize - k + 1;  
    
    for(int i = 0; i < end; i++) {
        int diff = nums[i + k - 1] - nums[i];
        if(diff < ans) {
            ans = diff;
        }
    }
    
    return ans;
}
