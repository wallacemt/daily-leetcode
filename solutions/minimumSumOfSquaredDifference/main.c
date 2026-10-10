long long minSumSquareDiff(int* nums1, int nums1Size, int* nums2, int nums2Size,
                           int k1, int k2) {
    long long k = (long long)k1 + k2;
    long long diffSum = 0;
    int maxDiff = 0;

    int* freq = (int*)calloc(100001, sizeof(int));
    if (!freq)
        return -1;

    // Calcula diferenças e frequências
    for (int i = 0; i < nums1Size; i++) {
        int diff = abs(nums1[i] - nums2[i]);
        if (diff > 0) {
            freq[diff]++;
            diffSum += diff;
            if (diff > maxDiff)
                maxDiff = diff;
        }
    }

    if (diffSum <= k) {
        free(freq);
        return 0;
    }

    // Reduz diferenças maiores primeiro (greedy)
    for (int d = maxDiff; d > 0 && k > 0; d--) {
        long long take = (k < freq[d]) ? k : freq[d];
        freq[d] -= (int)take;
        freq[d - 1] += (int)take;
        k -= take;
    }

    // Calcula resultado
    long long result = 0;
    for (int d = 1; d <= maxDiff; d++) {
        result += (long long)freq[d] * d * d;
    }

    free(freq);
    return result;
}