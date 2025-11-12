#include <stdlib.h>

static int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int minOperations(int* nums, int numsSize) {
    int n = numsSize;
    int count1 = 0;
    for (int i = 0; i < n; ++i) if (nums[i] == 1) ++count1;
    if (count1 > 0) return n - count1;

    int best = 1e9;
    for (int i = 0; i < n; ++i) {
        int g = nums[i];
        for (int j = i + 1; j < n; ++j) {
            g = gcd(g, nums[j]);
            if (g == 1) {
                int len = j - i + 1;
                if (len < best) best = len;
                break;
            }
        }
    }

    if (best == 1e9) return -1;
    return (best - 1) + (n - 1);
}
