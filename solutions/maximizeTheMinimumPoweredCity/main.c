long long maxPower(int* stations, int stationsSize, int r, int k) {
    long long* dp = (long long*)malloc((stationsSize + 1) * sizeof(long long));
    long long* power = (long long*)malloc(stationsSize * sizeof(long long));
    long long* add = (long long*)malloc((stationsSize + 1) * sizeof(long long));
    
    dp[0] = 0;
    for (int i = 0; i < stationsSize; i++){
        dp[i + 1] = dp[i] + stations[i];
    }
    
    for (int i = 0; i < stationsSize; i++){
        int left = (i - r) & ~((i - r) >> 31);
        int right = i + r + 1;
        if (right > stationsSize) right = stationsSize;
        power[i] = dp[right] - dp[left];
    }
    
    long long low = 0, high = dp[stationsSize] + k, ans = 0;
    while (low <= high){
        long long mid = low + ((high - low) >> 1); 
        memset(add, 0, (stationsSize + 1) * sizeof(long long));
        
        long long curr = 0, remain = k;
        int possible = 1;
        int end_limit = stationsSize - 2 * r - 1;
        
        for (int i = 0; i < stationsSize; i++){
            curr += add[i];
            long long total = power[i] + curr;
            if (total < mid){
                long long need = mid - total;
                remain -= need;
                if (remain < 0){
                    possible = 0;
                    break;
                }
                curr += need;
                if (i <= end_limit) 
                    add[i + 2 * r + 1] -= need;
            }
        }
        
        if (possible){
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    
    free(dp);
    free(power);
    free(add);
    
    return ans;
}