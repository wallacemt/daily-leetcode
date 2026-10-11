int sumOfSquares(int* nums, int numsSize) {
    int sum = 0;

    for (int i = 1; i * i <= numsSize; i++) {
        if (numsSize % i == 0) {
            int val_i = nums[i - 1];
            sum += val_i * val_i;

            int j = numsSize / i;
            int isDifferent = (i != j);
            int val_j = nums[j - 1];
            sum += isDifferent * val_j * val_j;
        }
    }

    return sum;
}