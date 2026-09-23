#include <limits.h>
#include <string.h>
 
int minOperations(int* nums, int numsSize, int x) {
    // Validação de entrada
    if (!nums || numsSize <= 0 || x < 0) {
        return -1;
    }
 
    long long totalSum = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < 0) {
            return -1;   
        }
        totalSum += nums[i];
    }
 
    if (totalSum < x) {
        return -1;
    }
 
    if (totalSum == x) {
        return numsSize;
    }
 
    long long target = totalSum - x;
    int minOps = INT_MAX;
 
    long long windowSum = 0;
    int left = 0;

    for (int right = 0; right < numsSize; right++) {
        windowSum += nums[right];
 
        while (windowSum > target && left <= right) {
            windowSum -= nums[left];
            left++;
        }
 
        if (windowSum == target) { 
            int operations = left + (numsSize - right - 1);
            minOps = (operations < minOps) ? operations : minOps;
        }
    }

    return (minOps == INT_MAX) ? -1 : minOps;
}