int countPartitions(int* nums, int numsSize) {
    int count = 0;
    int left_sum = 0;
    int total_sum = 0;
    for (int i = 0; i < numsSize; i++) {
        total_sum += nums[i];
    }
    for (int i = 0; i < numsSize - 1; i++) {
        left_sum += nums[i];
        int right_sum = total_sum - left_sum;
        if ((right_sum - left_sum) % 2 == 0) {
            count++;
        }
    }
    return count;
}
