int maxActiveSectionsAfterTrade(char* s) {
    if (s == NULL) return 0;
    int n = strlen(s);
    if (n == 0) return 0;
     
    int maxRuns = (n / 2) + 1;
    int* zeroRuns = (int*)malloc(maxRuns * sizeof(int));
    
    if (zeroRuns == NULL) return 0; // Segurança
    
    int runCount = 0;
    int ones = 0;
    int length = 0;
     
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            ones++;
            if (length > 0) {
                zeroRuns[runCount++] = length;
                length = 0;
            }
        } else {
            length++;
        }
    }
     
    if (length > 0) {
        zeroRuns[runCount++] = length;
    }
     
    if (runCount < 2) {
        return ones;
    }
     
    int best = zeroRuns[0] + zeroRuns[1];
    for (int i = 2; i < runCount; i++) {
        int current = zeroRuns[i - 1] + zeroRuns[i];
        if (current > best) {
            best = current;
        }
    }
    
    return ones + best;
}