int distinctSubseqII(char* s) {
    const int MOD = 1000000007;
    
    long long count[26] = {0};
    long long sum = 0;

    for (char* p = s; *p; p++) {
        long long total = (1 + sum) % MOD;
        int idx = *p - 'a';

        sum = (sum + total - count[idx] + MOD) % MOD;
        count[idx] = total;
    }

    return (int)sum;
}