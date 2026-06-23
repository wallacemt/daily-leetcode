#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool simulate(int* nums, int numsSize, int start, int direction) {
    int* temp = (int*)malloc(numsSize * sizeof(int));
    memcpy(temp, nums, numsSize * sizeof(int));
    
    int curr = start;
    
    while (curr >= 0 && curr < numsSize) {
        if (temp[curr] == 0) {
            curr += direction;
        } else {
            temp[curr]--;
            direction = -direction;
            curr += direction;
        }
    }
    bool allZero = true;
    for (int i = 0; i < numsSize; i++) {
        if (temp[i] != 0) {
            allZero = false;
            break;
        }
    }
    
    free(temp);
    return allZero;
}

int countValidSelections(int* nums, int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] == 0) {
            if (simulate(nums, numsSize, i, -1)) {
                count++;
            }
            if (simulate(nums, numsSize, i, 1)) {
                count++;
            }
        }
    }
    return count;
}