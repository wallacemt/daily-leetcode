#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int minPairSum(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compare);
    
    int maxSum = 0;
    int left = 0, right = numsSize - 1;
    
    while(left < right) {
        int currentSum = nums[left] + nums[right];
        if(currentSum > maxSum) {
            maxSum = currentSum;
        }
        left++;
        right--;
    }
    
    return maxSum;
}

