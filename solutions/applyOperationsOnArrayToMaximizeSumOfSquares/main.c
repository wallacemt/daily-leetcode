int maxSum(int* nums, int numsSize, int k) {
    const long long MOD = 1000000007LL;
    int bitCount[30] = {0};

    for (int i = 0; i < numsSize; i++) {
        for (int bit = 0; bit < 30; bit++) {
            bitCount[bit] += (nums[i] >> bit) & 1;
        }
    }

    long long result = 0;

    for (int i = 0; i < k; i++) {
        long long currentNum = 0;

        for (int bit = 29; bit >= 0; bit--) {
            int hasBit = (bitCount[bit] > 0);
            currentNum |= (hasBit << bit);
            bitCount[bit] -= hasBit;
        }

        result = (result + currentNum * currentNum) % MOD;
    }

    return (int)result;
}