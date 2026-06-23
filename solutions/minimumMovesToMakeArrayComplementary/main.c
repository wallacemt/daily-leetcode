int minMoves(int* nums, int numsSize, int limit) {
    int* dp = (int*)calloc(2 * limit + 2, sizeof(int));
    int half = numsSize / 2;
    
    // Processar pares
    for (int i = 0; i < half; i++) {
        int a = nums[i];
        int b = nums[numsSize - 1 - i];
        int mini = a < b ? a : b;
        int maxi = a > b ? a : b;
        
        dp[2] += 2;
        dp[mini + 1] -= 1;
        dp[mini + maxi] -= 1;
        dp[mini + maxi + 1] += 1;
        dp[maxi + limit + 1] += 1;
    }

    int res = numsSize;
    int moves = 0;
    
    for (int target = 2; target <= 2 * limit; target++) {
        moves += dp[target];
        if (moves < res) {
            res = moves;
        }
    }
    
    free(dp);
    return res;
}