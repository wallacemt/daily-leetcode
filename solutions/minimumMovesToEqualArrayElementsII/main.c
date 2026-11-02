#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int partition(int* nums, int left, int right, int pivotIndex) {
    int pivotValue = nums[pivotIndex]; 
    int temp = nums[pivotIndex];
    nums[pivotIndex] = nums[right];
    nums[right] = temp;

    int storeIndex = left;
    for (int i = left; i < right; i++) {
        if (nums[i] < pivotValue) { 
            temp = nums[i];
            nums[i] = nums[storeIndex];
            nums[storeIndex] = temp;
            storeIndex++;
        }
    }
 
    temp = nums[storeIndex];
    nums[storeIndex] = nums[right];
    nums[right] = temp;

    return storeIndex;
}

static int quickSelect(int* nums, int left, int right, int k) {
    if (left == right) return nums[left];

    int pivotIndex = left + rand() % (right - left + 1);
    pivotIndex = partition(nums, left, right, pivotIndex);

    if (k == pivotIndex) {
        return nums[k];
    } else if (k < pivotIndex) {
        return quickSelect(nums, left, pivotIndex - 1, k);
    } else {
        return quickSelect(nums, pivotIndex + 1, right, k);
    }
}

int minMoves2(int* nums, int numsSize) { 
    int median = quickSelect(nums, 0, numsSize - 1, numsSize / 2);
    int count = 0;
 
    for (int i = 0; i < numsSize; i++) {
        count += abs(nums[i] - median);
    }

    return count;
}

 