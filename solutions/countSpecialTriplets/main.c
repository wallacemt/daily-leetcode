#define MOD 1000000007

int specialTriplets(int* nums, int numsSize) {
    if (numsSize < 3) return 0;
    
    long long count = 0;
    int maxVal = 0;
    
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > maxVal) maxVal = nums[i];
    }
    
    int* leftFreq = (int*)calloc(maxVal + 1, sizeof(int));
    int* rightFreq = (int*)calloc(maxVal + 1, sizeof(int));
    
    for (int k = 2; k < numsSize; k++) {
        rightFreq[nums[k]]++;
    }
    
    leftFreq[nums[0]]++;
    
    for (int j = 1; j < numsSize - 1; j++) {
        int target = nums[j] * 2;
        
        if (target <= maxVal) {
            count = (count + (long long)leftFreq[target] * rightFreq[target]) % MOD;
        }
        
        rightFreq[nums[j + 1]]--;
        leftFreq[nums[j]]++;
    }
    
    free(leftFreq);
    free(rightFreq);
    
    return (int)count;
}