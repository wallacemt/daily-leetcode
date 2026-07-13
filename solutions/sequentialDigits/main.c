/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* sequentialDigits(int low, int high, int* returnSize) {
    int allSequenceDigits[45];
    int total = 0;

    int prev[9] = {1,2,3,4,5,6,7,8,9};
    int prevSize = 9;

    for(int i = 0; i < prevSize; i++) {
        allSequenceDigits[total++] = prev[i];
    }

    while(prevSize > 0) {
        int curr[9];
        int currSize = 0;

        for(int i = 0; i < prevSize; i++) {
            int num = prev[i];

            if(num % 10 < 9) {
                curr[currSize++] = num * 10 + (num % 10 + 1);
            } else {
                break;
            }
        }

        for(int i = 0; i < currSize; i++) {
            allSequenceDigits[total++] = curr[i];
        }

        memcpy(prev, curr, currSize * sizeof(int));
        prevSize = currSize;
    }

    int* result = (int*)malloc(45 * sizeof(int));
    *returnSize = 0;

    for(int i = 0; i < total; i++) {
        if(allSequenceDigits[i] >= low &&
           allSequenceDigits[i] <= high) {
            result[(*returnSize)++] = allSequenceDigits[i];
        } else if(allSequenceDigits[i] > high) {
            break;
        }
    }

    return result;
}