int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

bool isGood(int* nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), cmp);
    for (int i = 0; i < numsSize - 1; i++) {
        if (nums[i] != i + 1) {
            return false;
        }
    }
    return nums[numsSize - 1] == numsSize - 1;

}