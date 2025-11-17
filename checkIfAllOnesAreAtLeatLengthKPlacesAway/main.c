#include <stdbool.h>
bool kLengthApart(int* nums, int numsSize, int k) {
    int prev = -k - 1; 
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 1) {
            if (i - prev - 1 < k) return false;
            prev = i;
        }
    }
    return true;
}
