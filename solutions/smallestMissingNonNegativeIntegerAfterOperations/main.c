int findSmallestInteger(int* nums, int numsSize, int value) {
    int count[value];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < numsSize; i++) {
        int mod = nums[i] % value;
        if (mod < 0) {
            mod += value;
        }
        count[mod]++;
    }
    int mex = 0;
    while (1) {
        int mod = mex % value;
        if (count[mod] == 0) {
            return mex;
        }
        count[mod]--;
        mex++;
    }
    return mex;
}