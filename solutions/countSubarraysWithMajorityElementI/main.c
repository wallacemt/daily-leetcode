#include <stdio.h>

long long countMajoritySubarrays(int* nums, int numsSize, int target) {
    int n = numsSize;
    long long ans = 0;

    for (int l = 0; l < n; l++) {
        int targetCount = 0;
        int nonTargetCount = 0;

        for (int r = l; r < n; r++) {
       
            if (nums[r] == target) {
                targetCount++;
            } else {
                nonTargetCount++;
            }
 
            if (targetCount * 2 > r - l + 1) {
                ans++;
            }
        }
    }

    return ans;
}