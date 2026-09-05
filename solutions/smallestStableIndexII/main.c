#include <limits.h>

int firstStableIndex(int* nums, int numsSize, int k) {
    int n = numsSize;
    int maxi = INT_MIN;
    int mini = INT_MAX;

    int rightMini[n];

    for (int idx = n - 1; idx >= 0; idx--) {
        if (nums[idx] < mini) {
            mini = nums[idx];
        }
        rightMini[idx] = mini; 
    }
    for (int idx = 0; idx < n; idx++) {
        if (nums[idx] > maxi) {
            maxi = nums[idx];
        }

        if (maxi - rightMini[idx] <= k) {
            return idx;
        }
    }

    return -1;
}