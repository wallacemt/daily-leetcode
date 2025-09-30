int triangularSum(int* nums, int numsSize) {
    while (numsSize > 1) {
        for (int i = 0; i < numsSize - 1; i++) {
            nums[i] = (nums[i] + nums[i + 1]) % 10;
        }
        numsSize--;
    }
    if (numsSize == 1) {
        return nums[0];
    } else {
        return 0;

    }   
    
    return 0;
}