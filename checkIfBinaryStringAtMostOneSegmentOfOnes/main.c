bool checkOnesSegment(const char* s) {
    for(int i = 1; s[i]; i++) {
        if(s[i] == '1' && s[i - 1] == '0') 
            return false;
    }
    return true;
}
