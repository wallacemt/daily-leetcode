#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Constants for infinity and frequency adjustments
const long long kInfinity = 9223372036854775807LL / 2;
const int kFreqDecr = -1;
const int kFreqIncr = 1;

// Fenwick Tree structure for managing frequency and sum operations
typedef struct {
    int treeSz;
    long long* tree;
} FenwickTree;

// Create a new Fenwick Tree
FenwickTree* createTree(int treeSz) {
    FenwickTree* ft = (FenwickTree*)malloc(sizeof(FenwickTree));
    if (!ft) return NULL; // Check for allocation success
    ft->treeSz = treeSz;
    ft->tree = (long long*)calloc(treeSz + 1, sizeof(long long));
    return ft;
}

// Free the Fenwick Tree
void freeTree(FenwickTree* ft) {
    free(ft->tree);
    free(ft);
}

// Update the Fenwick Tree with a value at a specific index
void addVal(FenwickTree* ft, int idx, long long num) {
    for (; idx <= ft->treeSz; idx += idx & -idx) {
        ft->tree[idx] += num;
    }
}

// Query the cumulative frequency or sum up to a specific index
long long queryPref(FenwickTree* ft, int idx) {
    long long sum = 0;
    for (; idx > 0; idx -= idx & -idx) {
        sum += ft->tree[idx];
    }
    return sum;
}

// Find the k-th order statistic using binary lifting
int findKth(FenwickTree* ft, long long medianIdx) {
    int currIdx = 0;
    long long sum = 0;
    int maxBitIdx = 0;

    while ((1 << (maxBitIdx + 1)) <= ft->treeSz) {
        maxBitIdx++;
    }

    for (int step = 1 << maxBitIdx; step > 0; step >>= 1) {
        int nextIdx = currIdx + step;
        if (nextIdx <= ft->treeSz && sum + ft->tree[nextIdx] < medianIdx) {
            currIdx = nextIdx;
            sum += ft->tree[nextIdx];
        }
    }

    return currIdx + 1;
}

// Get the compressed ID for a target value
int getCompressedId(int* uniqueNums, int uniqueTot, int target) {
    int l = 0, r = uniqueTot - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (uniqueNums[m] == target) return m + 1;
        if (uniqueNums[m] < target) l = m + 1;
        else r = m - 1;
    }
    return 1;
}

// Compare two integers for qsort
int cmpInts(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

// Calculate the costs for each window
long long callWndwCost(
    FenwickTree* valFreqs,
    FenwickTree* sums,
    int* uniqueNums,
    int uniqueTot,
    int subarrSz
) {
    long long medianIdx = (subarrSz + 1) / 2;
    int medianId = findKth(valFreqs, medianIdx);
    long long medianValue = uniqueNums[medianId - 1];

    long long leftCnt = queryPref(valFreqs, medianId);
    long long leftSum = queryPref(sums, medianId);
    long long totalSum = queryPref(sums, uniqueTot);
    long long rightCnt = subarrSz - leftCnt;
    long long rightSum = totalSum - leftSum;

    return (medianValue * leftCnt - leftSum) + (rightSum - medianValue * rightCnt);
}

// Calculate window costs for the array
long long* calcWndwCosts(int* nums, int numsSize, int subarrSz) {
    long long* wndwCosts = (long long*)malloc(numsSize * sizeof(long long));
    int* uniqueNums = (int*)malloc(numsSize * sizeof(int));
    if (!wndwCosts || !uniqueNums) return NULL; // Check for allocation success

    memcpy(uniqueNums, nums, numsSize * sizeof(int));

    qsort(uniqueNums, numsSize, sizeof(int), cmpInts);
    int uniqueTot = 0;
    if (numsSize > 0) {
        uniqueNums[0] = uniqueNums[0];
        uniqueTot = 1;
        for (int i = 1; i < numsSize; i++) {
            if (uniqueNums[i] != uniqueNums[uniqueTot - 1]) {
                uniqueNums[uniqueTot++] = uniqueNums[i];
            }
        }
    }

    FenwickTree* valFreqs = createTree(uniqueTot);
    FenwickTree* sums = createTree(uniqueTot);
    if (!valFreqs || !sums) return NULL; // Check for allocation success

    void addToTrees(int num, int freqDelta) {
        int compId = getCompressedId(uniqueNums, uniqueTot, num);
        long long weightedDelta = (long long)num * freqDelta;
        addVal(valFreqs, compId, freqDelta);
        addVal(sums, compId, weightedDelta);
    }

    for (int i = 0; i < subarrSz; i++) {
        addToTrees(nums[i], kFreqIncr);
    }
    wndwCosts[subarrSz - 1] = callWndwCost(valFreqs, sums, uniqueNums, uniqueTot, subarrSz);

    for (int i = subarrSz; i < numsSize; i++) {
        addToTrees(nums[i - subarrSz], kFreqDecr);
        addToTrees(nums[i], kFreqIncr);
        wndwCosts[i] = callWndwCost(valFreqs, sums, uniqueNums, uniqueTot, subarrSz);
    }

    freeTree(valFreqs);
    freeTree(sums);
    free(uniqueNums);
    return wndwCosts;
}

// Calculate the minimum operations required to equalize subarrays
long long minOperations(int* nums, int numsSize, int subarrSz, int reqSubarrsTot) {
    long long* wndwCosts = calcWndwCosts(nums, numsSize, subarrSz);
    if (!wndwCosts) return -1; // Check for allocation success

    long long* currMinCosts = (long long*)calloc(numsSize + 1, sizeof(long long));
    long long* nextMinCosts = (long long*)malloc((numsSize + 1) * sizeof(long long));
    if (!currMinCosts || !nextMinCosts) return -1; // Check for allocation success

    for (int subarrCnt = 1; subarrCnt <= reqSubarrsTot; subarrCnt++) {
        for (int i = 0; i <= numsSize; i++) {
            nextMinCosts[i] = kInfinity;
        }

        int startIdx = subarrCnt * subarrSz;

        for (int dpIdx = startIdx; dpIdx <= numsSize; dpIdx++) {
            long long costIfSkipped = nextMinCosts[dpIdx - 1];
            long long costIfTaken = currMinCosts[dpIdx - subarrSz] + wndwCosts[dpIdx - 1];

            nextMinCosts[dpIdx] = (costIfTaken < costIfSkipped) ? costIfTaken : costIfSkipped;
        }

        long long* temp = currMinCosts;
        currMinCosts = nextMinCosts;
        nextMinCosts = temp;
    }

    long long minCost = currMinCosts[numsSize];

    free(wndwCosts);
    free(currMinCosts);
    free(nextMinCosts);

    return minCost;
}
