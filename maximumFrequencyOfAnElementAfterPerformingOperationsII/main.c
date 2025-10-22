int cmp(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}

int maxFrequency(int* nums, int n, int k, int maxSteps) {
    qsort(nums, n, sizeof(int), cmp);
    int l = 0, r = 0, i = 0;
    int res = 0;
    int upper, lower, range = k << 1;
    
    while (i < n) {
        int x = nums[i], same = 0;
        upper = x + k;
        lower = x - k;
        
        while (i < n && nums[i] == x) {
            ++same;
            ++i;
        }
        
        while (r < n && nums[r] <= upper) ++r;
        
        while (l < i && nums[l] < lower) ++l;
        
        int steps = (same + maxSteps < r - l) ? same + maxSteps : r - l;
        res = (steps > res) ? steps : res;
    }

    l = r = 0;
    while (r < n) {
        while (r < n && nums[r] - nums[l] <= range) ++r;
        
        int steps = (maxSteps < r - l) ? maxSteps : r - l;
        res = (steps > res) ? steps : res;
        
        ++l;
        if (l == r && r < n) ++r;
    }

    return res;
}