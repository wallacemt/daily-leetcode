
int minimumSumSubarray(int* nums, int numsSize, int l, int r) {
    int ans = INT_MAX;

    for (int size = l; size <= r; size++) {
        int sum = 0;
 
        for (int i = 0; i < size; i++) {
            sum += nums[i];
        }

        if (sum > 0 && sum < ans) {
            ans = sum;
        }
 
        for (int i = size; i < numsSize; i++) {
            sum += nums[i];
            sum -= nums[i - size];

            if (sum > 0 && sum < ans) {
                ans = sum;
            }
        }
    }

    return ans == INT_MAX ? -1 : ans;
}