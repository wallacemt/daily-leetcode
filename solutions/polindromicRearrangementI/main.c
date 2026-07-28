char* smallestPalindrome(char* s) {
    int freq[26] = {0};  
    int n = strlen(s);
    
    // Contagem de frequências - acesso direto mais rápido
    for(int i = 0; i < n; i++) {
        freq[s[i] - 'a']++;
    }
    
    char *ans = malloc((n + 1) * sizeof(char));
    ans[n] = '\0';
    
    if(n == 1) {
      
        for(int i = 0; i < 26; i++) {
            if(freq[i] > 0) {
                ans[n/2] = 'a' + i;
                break;
            }
        }
        return ans;
    }
    
    int index = 0;
    
  
    for(int i = 0; i < 26; i++) {
        int count = freq[i] >> 1;  
        for(int j = 0; j < count; j++) {
            ans[index] = 'a' + i;
            ans[n - 1 - index] = 'a' + i;
            index++;
        }
    }
    
    // Se comprimento é ímpar, encontra primeiro caractere ímpar
    if(n & 1) {  // Verificação de bit é mais rápida que modulo
        for(int i = 0; i < 26; i++) {
            if(freq[i] & 1) {  // Verifica bit menos significativo
                ans[n >> 1] = 'a' + i;
                break;
            }
        }
    }
    
    return ans;
}