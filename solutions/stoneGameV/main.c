int dfs(int* stoneValue, int left, int right, int** f, int* prefixSum) {
    if (left == right) {
        return 0;
    }
    if (f[left][right] != 0) {
        return f[left][right];
    }
 
    int sum = prefixSum[right + 1] - prefixSum[left];
    int suml = 0;
    
    for (int i = left; i < right; ++i) {
        suml += stoneValue[i];
        int sumr = sum - suml;
        
        if (suml < sumr) {
            f[left][right] = fmax(f[left][right], 
                dfs(stoneValue, left, i, f, prefixSum) + suml);
        } else if (suml > sumr) {
            f[left][right] = fmax(f[left][right], 
                dfs(stoneValue, i + 1, right, f, prefixSum) + sumr);
        } else {
            f[left][right] = fmax(f[left][right], 
                fmax(dfs(stoneValue, left, i, f, prefixSum),
                     dfs(stoneValue, i + 1, right, f, prefixSum)) + suml);
        }
    }
    return f[left][right];
}

int stoneGameV(int* stoneValue, int stoneValueSize) {
    int n = stoneValueSize;
     
    int* prefixSum = (int*)malloc(sizeof(int) * (n + 1));
    prefixSum[0] = 0;
    for (int i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
    }
     
    int** f = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        f[i] = (int*)calloc(n, sizeof(int));
    }
    
    int result = dfs(stoneValue, 0, n - 1, f, prefixSum);
     
    for (int i = 0; i < n; i++) {
        free(f[i]);
    }
    free(f);
    free(prefixSum);
    
    return result;
}