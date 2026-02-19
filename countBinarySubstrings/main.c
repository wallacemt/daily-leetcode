int countBinarySubstrings(char* s) {
    int n = strlen(s);
    int groups[n];
    int groupCount = 0;
    int count = 1;
    
    for (int i = 1; i < n; i++) {
        if (s[i] == s[i-1]) {
            count++;
        } else {
            groups[groupCount++] = count;
            count = 1;
        }
    }
    groups[groupCount++] = count;
    
    int res = 0;
    for (int i = 1; i < groupCount; i++) {
        res += (groups[i-1] < groups[i]) ? groups[i-1] : groups[i];
    }
    return res;
}
