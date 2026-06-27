int cmp(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);
}

int lowerBound(int* nums, int n, long long target) {
    int l = 0, r = n;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if ((long long)nums[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

int getCount(int* nums, int n, long long target) {
    int left = lowerBound(nums, n, target);
    int right = lowerBound(nums, n, target + 1);
    return right - left;
}

int exists(int* nums, int n, long long target) {
    int pos = lowerBound(nums, n, target);
    return pos < n && (long long)nums[pos] == target;
}

int maximumLength(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);

    int res = 0;

    for (int i = 0; i < numsSize; i++) {
        long long key = nums[i];
        int total = 0;

        if (key == 1) {
            int cnt = getCount(nums, numsSize, 1);
            total = (cnt % 2 == 1) ? cnt : cnt - 1;
        } else {
            while (
                getCount(nums, numsSize, key) >= 2 &&
                key <= 1000000000LL / key &&
                exists(nums, numsSize, key * key)
            ) {
                total += 2;
                key = key * key;
            }

            total += 1;
        }

        if (total > res)
            res = total;
    }

    return res;
}