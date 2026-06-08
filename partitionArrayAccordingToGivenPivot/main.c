#include <stdlib.h>

int* pivotArray(int* nums, int numsSize, int pivot, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    

    int lessCount = 0, equalCount = 0;
    for(int i = 0; i < numsSize; i++) {
        if(nums[i] < pivot) lessCount++;
        else if(nums[i] == pivot) equalCount++;
    }
    
   
    int lessPos = 0;
    int equalPos = lessCount;
    int greaterPos = lessCount + equalCount;
    
    // Preencher resultado em uma única passagem
    for(int i = 0; i < numsSize; i++) {
        if(nums[i] < pivot) {
            result[lessPos++] = nums[i];
        } else if(nums[i] == pivot) {
            result[equalPos++] = nums[i];
        } else {
            result[greaterPos++] = nums[i];
        }
    }
    
    *returnSize = numsSize;
    return result;
}