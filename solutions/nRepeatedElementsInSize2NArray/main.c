int repeatedNTimes(int* nums, int numsSize) {
    for (int i = 0; i < numsSize - 2; i++) {
        if (nums[i] == nums[i + 1] || nums[i] == nums[i + 2]) {
            return nums[i];
        }
    }
    return nums[numsSize - 1];
}
