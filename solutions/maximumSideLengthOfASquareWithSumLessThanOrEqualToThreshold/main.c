int maxSideLength(int** mat, int matSize, int* matColSize, int threshold) {
    int m = matSize;
    int n = matColSize[0];
    int maxDim = m < n ? m : n;
    
    int* prefixData = (int*)calloc((m + 1) * (n + 1), sizeof(int));
    int** prefix = (int**)malloc((m + 1) * sizeof(int*));
    
    for (int i = 0; i <= m; i++) {
        prefix[i] = prefixData + i * (n + 1);
    }
    
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            prefix[i + 1][j + 1] = mat[i][j] + prefix[i][j + 1] 
                                   + prefix[i + 1][j] - prefix[i][j];
        }
    }
    
    int left = 0, right = maxDim, ans = 0;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        int found = 0;
        
        for (int i = mid; i <= m && !found; i++) {
            for (int j = mid; j <= n && !found; j++) {
                int total = prefix[i][j] - prefix[i - mid][j] 
                          - prefix[i][j - mid] + prefix[i - mid][j - mid];
                if (total <= threshold) {
                    found = 1;
                }
            }
        }
        
        if (found) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    free(prefix);
    free(prefixData);
    
    return ans;
}