int maxNumberOfBalloons(char* text) {
    int count[5] = {0}; 
    
    for (int i = 0; text[i]; i++) {
        switch (text[i]) {
            case 'b': count[0]++; break;
            case 'a': count[1]++; break;
            case 'l': count[2]++; break;
            case 'o': count[3]++; break;
            case 'n': count[4]++; break;
        }
    }
    
    count[2] >>= 1; 
    count[3] >>= 1;

    int ans = count[0];
    for (int i = 1; i < 5; i++) {
        if (count[i] < ans) {
            ans = count[i];
        }
    }
    
    return ans;
}