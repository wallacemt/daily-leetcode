int maxIncreasingSubarrays(int* nums, int numsSize) {
    int up = 1, preUp = 0, res = 0;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i-1]) {
            up++;
        } else {
            preUp = up;
            up = 1;
        }
        int candidate = (up >> 1);
        int minPair = (preUp < up) ? preUp : up;
        res = (candidate > minPair) ? ((candidate > res) ? candidate : res): ((minPair > res) ? minPair : res);
    }
    return res;
}