#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

long long lcm(int a, int b) {
    return ((long long)a * b) / gcd(a, b);
}


int* replaceNonCoprimes(int* nums, int numsSize, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    int size = 0;
    
    for (int i = 0; i < numsSize; i++) {
        result[size++] = nums[i];
        
        while (size >= 2 && gcd(result[size-2], result[size-1]) > 1) {
            long long newVal = lcm(result[size-2], result[size-1]);
            size--;
            result[size-1] = (int)newVal; 
        }
    }
    
    *returnSize = size;
    return result;
}
