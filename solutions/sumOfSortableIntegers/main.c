#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

int sortableIntegers(int* nums, int numsSize) {
    int n = numsSize;

    // Prefix max and suffix min arrays
    int* prefMax = (int*)malloc((n + 1) * sizeof(int));
    int* suffMin = (int*)malloc((n + 1) * sizeof(int));
    int* drop = (int*)calloc(n, sizeof(int));

    // Initialize prefix maximums
    prefMax[0] = INT_MIN; // Use INT_MIN for proper comparisons
    for (int i = 0; i < n; i++) {
        prefMax[i + 1] = (prefMax[i] > nums[i]) ? prefMax[i] : nums[i];
    }

    // Initialize suffix minimums
    suffMin[n] = INT_MAX;
    for (int i = n - 1; i >= 0; i--) {
        suffMin[i] = (suffMin[i + 1] < nums[i]) ? suffMin[i + 1] : nums[i];
    }

    // Count the number of drops (decreasing order breaks)
    for (int i = 1; i < n; i++) {
        drop[i] = drop[i - 1] + (nums[i - 1] > nums[i]);
    }

    int ans = 0;

    // Check for each divisor k
    for (int k = 1; k <= n; k++) {
        if (n % k != 0) continue; // k must divide n

        bool ok = true;

        // Check each block of size k
        for (int i = 0; i < n; i += k) {
            int j = i + k - 1;

            // Count decreases within the block
            int decreases = drop[j] - drop[i];
            decreases += (nums[j] > nums[i]); // Check if the last element is greater than the first

            if (decreases > 1) {
                ok = false;
                break;
            }

            // Check prefix maximum and suffix minimum
            if (i > 0 && prefMax[i] > suffMin[i]) {
                ok = false;
                break;
            }
        }

        if (ok) ans += k; // Count valid k
    }

    free(prefMax);
    free(suffMin);
    free(drop);

    return ans;
}

 