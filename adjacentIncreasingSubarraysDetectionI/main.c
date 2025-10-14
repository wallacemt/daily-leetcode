bool hasIncreasingSubarrays(int* nums, int numsSize, int k) {
    if (numsSize < 2 * k) return false;
    
    for (int i = 0; i <= numsSize - 2 * k; i++) {
        bool firstIncreasing = true;
        for (int j = i; j < i + k - 1; j++) {
            if (nums[j] >= nums[j + 1]) {
                firstIncreasing = false;
                break;
            }
        }
        
        if (!firstIncreasing) continue;
    
        bool secondIncreasing = true;
        for (int j = i + k; j < i + 2 * k - 1; j++) {
            if (nums[j] >= nums[j + 1]) {
                secondIncreasing = false;
                break;
            }
        }
        
        if (secondIncreasing) return true;
    }
    
    return false;
}
