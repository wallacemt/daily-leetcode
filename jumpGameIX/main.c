int* maxValue(int* nums, int numsSize, int* returnSize) {
    int n = numsSize;
    int* res = (int*)malloc(sizeof(int) * n);
    res[0] = nums[0];
    for (int i = 1; i < n; i++) {
        res[i] = res[i - 1] > nums[i] ? res[i - 1] : nums[i];
    }
    int min_idx = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        if (res[i] > nums[min_idx]) {
            res[i] = res[min_idx];
        }
        if (nums[i] < nums[min_idx]) {
            min_idx = i;
        }
    }
    *returnSize = n;
    return res;
}