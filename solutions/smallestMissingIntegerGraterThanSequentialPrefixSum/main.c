int missingInteger(int* nums, int numsSize) {
    // Caso especial: array com um elemento
    if (numsSize == 1) {
        return nums[0] + 1;
    }
 
    int prefixSum = nums[0];
    int i = 1;
    
    while (i < numsSize && nums[i] == nums[i - 1] + 1) {
        prefixSum += nums[i];
        i++;
    }
 
    int present[101] = {0};
    
    // Preencher array de presença
    for (int j = 0; j < numsSize; j++) {
        if (nums[j] <= 100) {
            present[nums[j]] = 1;
        }
    }
 
    while (prefixSum <= 100 && present[prefixSum]) {
        prefixSum++;
    }

    return prefixSum;
}