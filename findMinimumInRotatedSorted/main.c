#include <stdio.h>

int findMin(int* nums, int numsSize) {
    int i = 0;
    int j = numsSize - 1;
    
    while (i < j) {
        int mid = i + (j - i) / 2;  // Evita overflow
        
        if (nums[mid] > nums[j]) {
            i = mid + 1;
        } else {
            j--;
        }
    }
    
    return nums[i];
}
