#include <stdbool.h>
#include <limits.h>

bool uniformArray(int* numsIn_, int numsSize) {
    if (!numsIn_ || numsSize <= 0) {
        return true;
    }

    int minNum = INT_MAX;
    bool hasOdd = false;

    for (int i = 0; i < numsSize; ++i) {
        int num = numsIn_[i];
        
        if (num & 1) {
            hasOdd = true;
        }
        if (num < minNum) {
            minNum = num;
        }
    }

    return (minNum & 1) || !hasOdd;
}