#pragma GCC optimize("O3, unroll-loops")
char* removeOuterParentheses(char* s) {
 int balance = 0, j = 0;
    for (int i = 0; s[i]; i++) {
        char c = s[i];
        int delta = (c == '(') - (c == ')');
        balance += delta; 
        int isOuter = ((balance == 1 && delta == 1) || (balance == 0 && delta == -1));
        s[j] = c;
        j += !isOuter;
    }
    s[j] = '\0';
    return s;
}