int compare(const void* a, const void* b) {
    int x = abs(*(int*)a);
    int y = abs(*(int*)b);
    return x - y;
}

long long maxAlternatingSum(int* nums, int numsSize) {
    long long ans = 0;
    int n = numsSize / 2;

    qsort(nums, numsSize, sizeof(int), compare);

    // Soma maiores (segunda metade)
    for (int i = n; i < numsSize; i++) {
        ans += (long long)nums[i] * nums[i];
    }

    // Subtrai menores (primeira metade)
    for (int i = 0; i < n; i++) {
        ans -= (long long)nums[i] * nums[i];
    }

    return ans;
}
