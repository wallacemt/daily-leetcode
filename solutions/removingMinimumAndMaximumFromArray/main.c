#include <stdio.h>
#include <stdlib.h>

static inline int min(int a, int b) {
    return a < b ? a : b;
}

int minimumDeletions(int* nums, int numsSize) {
    if (!nums || numsSize <= 0) {
        return 0;
    }

    if (numsSize == 1) {
        return 1;
    }

    int minVal = nums[0], maxVal = nums[0];
    int minIdx = 0, maxIdx = 0;

    for (int i = 1; i < numsSize; i++) {
        int x = nums[i];
        
        if (x < minVal) {
            minVal = x;
            minIdx = i;
        }
        if (x > maxVal) {
            maxVal = x;
            maxIdx = i;
        }
    }

    if (minVal == maxVal) {
        return numsSize - 1;
    }

    if (minIdx > maxIdx) {
        int temp = minIdx;
        minIdx = maxIdx;
        maxIdx = temp;
    }

    int deleteFromStart = maxIdx + 1;
    int deleteFromEnd = numsSize - minIdx;
    int deleteFromMiddle = (minIdx + 1) + (numsSize - maxIdx);

    return min(deleteFromStart, min(deleteFromEnd, deleteFromMiddle));
}