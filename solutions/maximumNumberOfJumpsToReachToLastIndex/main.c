int maximumJumps(int* nums, int numsSize, int target) {
    int* dp = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        dp[i] = -1;
    }
    dp[0] = 0;
    for (int i = 1; i < numsSize; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (-target <= nums[i] - nums[j] &&
                nums[i] - nums[j] <= target) {
                if (dp[j] > -1) {
                    if (dp[j] + 1 > dp[i]) {
                        dp[i] = dp[j] + 1;
                    }
                }
            }
        }
    }

    int ans = dp[numsSize - 1];
    free(dp);
    return ans;
}