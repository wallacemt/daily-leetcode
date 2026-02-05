
int* constructTransformedArray(int* nums, int numsSize, int* returnSize) {
    int n = numsSize;
    int* res = (int*)malloc(sizeof(int) * n);
    *returnSize = n;

    for (int i = 0; i < n; i++) {
        long long j = (long long)i + nums[i];
        j %= n;
        if (j < 0) 
            j += n;
        res[i] = nums[(int)j];
    }
    return res;
}
