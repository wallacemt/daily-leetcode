int numberOfSets(int n, int k) {
    const long long MOD = 1000000007LL;

    long long* dp = malloc(n * sizeof(long long));
    long long* prefixSums = calloc(n + 1, sizeof(long long));

    for (int j = 0; j < n; j++) {
        dp[j] = 1;
        prefixSums[j + 1] = (prefixSums[j] + dp[j]) % MOD;
    }

    for (int i = 0; i < k; i++) {
        dp[0] = 0;

        for (int j = 1; j < n; j++) {
            dp[j] = (dp[j - 1] + prefixSums[j]) % MOD;
        }

        prefixSums[0] = 0;

        for (int j = 0; j < n; j++) {
            prefixSums[j + 1] = (prefixSums[j] + dp[j]) % MOD;
        }
    }

    int result = (int)dp[n - 1];

    free(dp);
    free(prefixSums);

    return result;
}