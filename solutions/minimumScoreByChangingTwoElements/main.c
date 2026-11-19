#include <stdlib.h>


int compare(const void* a, const void* b) {
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;
    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;
}
 
int minimizeSum(int* nums, int numsSize) { 
    if (numsSize <= 3) {
        return 0;
    }

    qsort(nums, numsSize, sizeof(int), compare);
 
    int opt1 = nums[numsSize - 1] - nums[2];
     
    int opt2 = nums[numsSize - 2] - nums[1];
     
    int opt3 = nums[numsSize - 3] - nums[0];
 
    int min_val = opt1;
    if (opt2 < min_val) min_val = opt2;
    if (opt3 < min_val) min_val = opt3;

    return min_val;
}