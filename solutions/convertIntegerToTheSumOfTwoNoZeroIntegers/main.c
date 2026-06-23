#include <stdbool.h>

bool hasNoZero(int num) {
    while (num > 0) {
        if (num % 10 == 0) {
            return false;
        }
        num /= 10;
    }
    return true;
}

int* getNoZeroIntegers(int n, int* returnSize) {
    int* result = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;
    
    for (int i = 1; i < n; i++) {
        int j = n - i;
        if (hasNoZero(i) && hasNoZero(j)) {
            result[0] = i;
            result[1] = j;
            return result;
        }
    }
    
    return result;
}
