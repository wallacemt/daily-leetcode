static int compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findMissingElements(int* nums, int numsSize, int* returnSize) {
    qsort(nums, numsSize, sizeof(int), compare);

    int capacity = nums[numsSize - 1] - nums[0];
    int* ans = (int*)malloc(sizeof(int) * capacity);
    int size = 0;
 
    int j = 0; // pointer para o array nums
    
    for (int x = nums[0]; x < nums[numsSize - 1]; x++) {
        
        if (j < numsSize && nums[j] == x) {
            j++;
        } else { 
            ans[size++] = x;
        }
    }

    *returnSize = size;
    return ans;
}