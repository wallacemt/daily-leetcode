#include <stdlib.h>

int firstStableIndex(int* nums, int numsSize, int k) {
    if (!nums || numsSize <= 0 || k < 0) {
        return -1;
    }

    int* minNext = (int*)malloc(sizeof(int) * numsSize);
    
    minNext[numsSize - 1] = nums[numsSize - 1];
    for (int i = numsSize - 2; i >= 0; i--) {
        minNext[i] = (minNext[i + 1] < nums[i]) ? minNext[i + 1] : nums[i];
    }

    int maxPrev = nums[0];
    int answer = -1;

    for (int i = 0; i < numsSize; i++) {
        if (maxPrev - minNext[i] <= k) {
            answer = i;
            break;
        }
        if (nums[i] > maxPrev) {
            maxPrev = nums[i];
        }
    }

    free(minNext);
    return answer;
}