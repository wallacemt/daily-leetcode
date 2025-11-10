#include <stdlib.h>

int minOperations(int* nums, int numsSize) {
    int *stack = (int*)malloc(numsSize * sizeof(int));
    int top = 0;
    int res = 0;
    for (int i = 0; i < numsSize; ++i) {
        int v = nums[i];
        if (v == 0) {
            top = 0; 
            continue;
        }
        while (top > 0 && stack[top - 1] > v) --top;
        if (top == 0 || stack[top - 1] < v) {
            stack[top++] = v;
            ++res;
        }
    }
    free(stack);
    return res;
}
