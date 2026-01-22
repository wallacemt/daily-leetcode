#include <stdio.h>
#include <string.h>
#include <limits.h>


static int is_sorted(int* nums, int n){
    for(int i = 1; i < n; i++) {
        if(nums[i] < nums[i - 1]) return 0;
    }
    return 1;
}

int minimumPairRemoval(int* nums, int numsSize) {
    if(nums== NULL || numsSize <= 0) return 0;

    if(numsSize ==1) return 0;

    int* buffer = (int*)malloc(numsSize * sizeof(int));

    if (buffer == NULL) return -1;

    memcpy(buffer, nums, numsSize * sizeof(int));

    int n = numsSize;

    int opt = 0;

    while(!is_sorted(buffer, n) && n > 1) {
        long long min_sum = LLONG_MAX;
        int idx = 0;

        for (int i = 0; i < n - 1; i++) {
            long long pair_sum = (long long)buffer[i] + buffer[i + 1];
            if(pair_sum < min_sum) {
                min_sum = pair_sum;
                idx = i;
            }

        }

        buffer[idx] = (int)min_sum;
        memmove(&buffer[idx + 1], &buffer[idx + 2], (n - idx - 2) * sizeof(int));


        n--;
        opt++;
    }
    free(buffer);
    return opt;
}
