#include <stdint.h>
 
int climbStairs(int n, int* costs, int costsSize) {
    if (costsSize == 0) return 0;
 
    long long f0 = 0, f1 = 0, f2 = 0;

    for (int i = 0; i < costsSize; i++) { 
        long long opt1 = f2 + 1;
        long long opt2 = f1 + 4;
        long long opt3 = f0 + 9;

        long long minPrev = opt1;
        if (opt2 < minPrev) minPrev = opt2;
        if (opt3 < minPrev) minPrev = opt3;

        long long current = costs[i] + minPrev;
 
        f0 = f1;
        f1 = f2;
        f2 = current;
    }

    return (int)f2;
}