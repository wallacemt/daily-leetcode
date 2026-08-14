int maximumLengthSubstring(char* s) {
    int len = 0, start = 0;
    int freq[26] = {0};
    
    for (int i = 0; s[i]; i++) {
        int char_idx = s[i] - 'a';
        freq[char_idx]++;
         
        while (freq[char_idx] == 3) {
            freq[s[start++] - 'a']--;
        }
         
        int current_len = i - start + 1;
        if (current_len > len) {
            len = current_len;
        }
    }
    
    return len;
}