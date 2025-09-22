int maxFrequencyElements(int* nums, int numsSize) {
    int freq[101] = {0}; 
    int maxFreq = 0;
    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
        if (freq[nums[i]] > maxFreq) {
            maxFreq = freq[nums[i]];
        }
    }
    for (int i = 1; i <= 100; i++) {
        if (freq[i] == maxFreq) {
            result += freq[i];
        }
    }
    
    return result;
}
