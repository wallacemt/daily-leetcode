#include <stdlib.h>

int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int maxDistinctElements(int* nums, int numsSize, int k) {
    if (numsSize == 0) return 0;
    
    qsort(nums, numsSize, sizeof(int), compare);
    
    int distinctCount = 1;
    int lastUsed = nums[0] - k;
    
    for (int i = 1; i < numsSize; i++) {
        
        int minPossible = nums[i] - k;
        int maxPossible = nums[i] + k;
        
     
        int target = (lastUsed >= minPossible) ? lastUsed + 1 : minPossible;
        
         if (target <= maxPossible) {
            distinctCount++;
            lastUsed = target;
        }
       
    }
    
    return distinctCount;
}
