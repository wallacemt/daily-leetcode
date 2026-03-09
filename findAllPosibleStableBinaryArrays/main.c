#define MOD 1000000007
int numberOfStableArrays(int zero, int one, int limit) {
    int li = limit + 1;

    long long** dp0 = (long long**)malloc((zero + 1) * sizeof(long long*));
    long long** dp1 = (long long**)malloc((zero + 1) * sizeof(long long*));

    for (int i = 0; i <= zero; i++) {
        dp0[i] = (long long*)calloc(one + 1, sizeof(long long));
        dp1[i] = (long long*)calloc(one + 1, sizeof(long long));
    }

    for (int i = 1; i <= zero && i <= limit; i++) {
        dp0[i][0] = 1;
    }

    for (int j = 1; j <= one && j <= limit; j++) {
        dp1[0][j] = 1;
    }

    for (int i = 1; i <= zero; i++) {
        for (int j = 1; j <= one; j++) {
            long long sub1 = (i >= li) ? dp1[i - li][j] : 0;
            dp0[i][j] = (dp0[i - 1][j] + dp1[i - 1][j] - sub1 + MOD) % MOD;

            long long sub2 = (j >= li) ? dp0[i][j - li] : 0;
            dp1[i][j] = (dp0[i][j - 1] + dp1[i][j - 1] - sub2 + MOD) % MOD;
        }
    }

    int ans = (dp0[zero][one] + dp1[zero][one]) % MOD;

    for (int i = 0; i <= zero; i++) {
        free(dp0[i]);
        free(dp1[i]);
    }
    free(dp0);
    free(dp1);

    return ans;
}
