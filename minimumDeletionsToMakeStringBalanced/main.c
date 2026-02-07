int minimumDeletions(char* s) {
    int cnt = 0;   
    int del = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'b') {
            cnt++;
        } else {
            if (cnt > 0) {
                del++;
                cnt--;
            }
        }
    }
    return del;
}