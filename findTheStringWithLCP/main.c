char* findTheString(int** lcp, int lcpSize, int* lcpColSize) {
    int n = lcpSize;
    
    if (n == 0) {
        char* res = (char*)malloc(1);
        res[0] = '\0';
        return res;
    }
    
    int* s = (int*)calloc(n, sizeof(int));
    if (!s) return "";
    
    int val = 1;
    
    for (int i = 0; i < n; i++) {
        if (s[i] > 0) continue;
        
        if (val > 26) {
            free(s);
            return "";
        }
        
        for (int j = i; j < n; j++) {
            if (lcp[i][j] > 0) {
                s[j] = val;
            }
        }
        val++;
    }
    
    char* res = (char*)malloc(n + 1);
    if (!res) {
        free(s);
        return "";
    }
    
    for (int i = 0; i < n; i++) {
        res[i] = 'a' + s[i] - 1;
    }
    res[n] = '\0';
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int expected = 0;
            if (res[i] == res[j]) {
                expected = 1;
                if (i + 1 < n && j + 1 < n) {
                    expected += lcp[i + 1][j + 1];
                }
            }
            
            // Early termination se não corresponder
            if (lcp[i][j] != expected) {
                free(res);
                free(s);
                return "";
            }
        }
    }
    
    free(s);
    return res;
}