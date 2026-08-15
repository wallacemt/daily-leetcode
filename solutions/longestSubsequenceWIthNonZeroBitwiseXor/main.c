int longestSubsequence(int* nums, int numsSize) {
    int xr = 0;
    int hasNonZero = 0;

    for (int i = 0; i < numsSize; i++) {
        xr ^= nums[i];
        hasNonZero |= (nums[i] != 0);   
    }

    return (xr != 0) ? numsSize : (hasNonZero ? numsSize - 1 : 0);
}