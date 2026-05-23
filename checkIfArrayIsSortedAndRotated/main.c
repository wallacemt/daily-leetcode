bool check(int* nums, int numsSize) {
    int count = 0;
    
    for (int i = 1; i < numsSize && count <= 1; i++) {
        if (nums[i - 1] > nums[i]) {
            count++;
        }
    }

    if (count > 1) {
        return false;
    }

    if (nums[numsSize - 1] > nums[0]) {
        count++;
    }

    return count <= 1;
}
