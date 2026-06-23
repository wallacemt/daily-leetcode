#include <string.h>

int longestBalanced(char* s) {
    int n = strlen(s);
    int ans = 0;

    for (int i = 0; i < n; i++) {
        int freq[26] = {0};
        int maxFreq = 0;
        int uniqueCount = 0;

        for (int j = i; j < n; j++) {
            int idx = s[j] - 'a';
            
            if (freq[idx] == 0) {
                uniqueCount++;
            }
            
            freq[idx]++;
            
            if (freq[idx] > maxFreq) {
                maxFreq = freq[idx];
            }
            
            int length = j - i + 1;
            
            if (maxFreq * uniqueCount == length) {
                if (length > ans) {
                    ans = length;
                }
            }
        }
    }
    
    return ans;
}