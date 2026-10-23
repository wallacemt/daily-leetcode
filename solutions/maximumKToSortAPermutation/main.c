#include <stdio.h>

int sortPermutation(int* nums, int numsSize) {
    int missingValue = -1; 
 
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] != i) { 
            if (missingValue == -1) {
                missingValue = nums[i]; // Armazena o primeiro valor fora de lugar
            } else { 
                missingValue &= nums[i]; // Isso pode não ser o que você deseja
            }
        }
    }
 
    return missingValue == -1 ? 0 : missingValue;
}
 
