#include <stdlib.h>
#include <string.h>

int largestInteger(int* nums, int numsSize, int k) {
    if (numsSize < k) return -1;

    int numSubarrays = numsSize - k + 1;
     
    int* subarrayCount = (int*)calloc(51, sizeof(int));
    if (!subarrayCount) return -1;

    // Para cada subarray de tamanho k
    for (int i = 0; i < numSubarrays; i++) { 
        int* seen = (int*)calloc(51, sizeof(int));
        if (!seen) {
            free(subarrayCount);
            return -1;
        }
 
        for (int j = i; j < i + k; j++) {
            seen[nums[j]] = 1;
        }
 
        for (int val = 0; val <= 50; val++) {
            if (seen[val]) {
                subarrayCount[val]++;
            }
        }

        free(seen);
    }
 
    int ans = -1;
    for (int val = 50; val >= 0; val--) {
        if (subarrayCount[val] == 1) {
            ans = val;
            break;
        }
    }

    free(subarrayCount);
    return ans;
}