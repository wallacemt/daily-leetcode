char* smallestSubsequence(char* s) {
    int freq[26] = {0};
    bool vis[26] = {0};
     
    int n = 0;
    for (int i = 0; s[i]; i++) {
        freq[s[i] - 'a']++;
        n++;
    }
     
    char *stack = (char *)malloc((n + 1) * sizeof(char));
    if (!stack) return NULL;
    
    int top = -1;
    
    for (int i = 0; i < n; i++) {
        char ch = s[i];
        freq[ch - 'a']--;
        
        if (vis[ch - 'a'])
            continue;
         
        int ch_idx = ch - 'a';
        
        while (top != -1) {
            int top_idx = stack[top] - 'a';
             
            if (ch >= stack[top] || freq[top_idx] == 0)
                break;
            
            vis[top_idx] = false;
            top--;
        }
        
        stack[++top] = ch;
        vis[ch_idx] = true;
    }
    
    stack[top + 1] = '\0';
    return stack;
}