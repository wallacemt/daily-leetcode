#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int triangleNumber(int* nums, int numsSize) {
    if (numsSize < 3) return 0;
    qsort(nums, numsSize, sizeof(int), compare);
    
    int count = 0;
    
    for (int k = 2; k < numsSize; k++) {
        int left = 0, right = k - 1;
        
        while (left < right) {
            if (nums[left] + nums[right] > nums[k]) {
                count += (right - left);
                right--;
            } else {
                left++;
            }
        }
    }
    
    return count;
}
