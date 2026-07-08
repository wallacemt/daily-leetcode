 
int* sumAndMultiply(char* s, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    const int MOD = 1000000007;
    int n = strlen(s);
     
    int* idx = calloc(n + 1, sizeof(int));
    long long* val = calloc(n + 1, sizeof(long long));
    long long* total = calloc(n + 1, sizeof(long long));
    long long* pow10 = malloc((n + 1) * sizeof(long long));
     
    pow10[0] = 1;
    for (int i = 1; i <= n; i++) {
        pow10[i] = pow10[i - 1] * 10 % MOD;
    }
     
    int count = 0;
    long long prev_val = 0;
    long long prev_total = 0;
    
    for (int i = 0; i < n; i++) {
        int digit = s[i] - '0';
        
        if (digit != 0) {
            count++;
            prev_val = (prev_val * 10 + digit) % MOD;
            prev_total += digit;
            val[count] = prev_val;
            total[count] = prev_total;
        }
        
        idx[i + 1] = count;
    }
    
    int* ans = malloc(queriesSize * sizeof(int));
    *returnSize = queriesSize;
     
    for (int i = 0; i < queriesSize; i++) {
        int a = idx[queries[i][0]];
        int b = idx[queries[i][1] + 1];
        
        if (a == b) {
            ans[i] = 0;
            continue;
        }
        
        int length = b - a;
        long long num = (val[b] - val[a] * pow10[length]) % MOD;
        if (num < 0) num += MOD;
        
        long long digitSum = total[b] - total[a];
        ans[i] = (int)(num * digitSum % MOD);
    }
    
    free(idx);
    free(val);
    free(total);
    free(pow10);
    
    return ans;
}