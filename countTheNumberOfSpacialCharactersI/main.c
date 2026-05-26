int numberOfSpecialChars(const char* word) {
    if (!word) return 0;
    
    unsigned char appears[26] = {0};
    
    for (int i = 0; word[i] != '\0'; i++) {
        char c = word[i];
        if (c >= 'a' && c <= 'z') {
            appears[c - 'a'] |= 1;
        } else if (c >= 'A' && c <= 'Z') {
            appears[c - 'A'] |= 2;
        }
    }
    
    int ans = 0;
    for (int i = 0; i < 26; i++) {
        ans += (appears[i] == 3);  // Mais rápido que if
    }
    
    return ans;
}