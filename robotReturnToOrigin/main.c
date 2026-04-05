bool judgeCircle(char* moves) {
    int valh = 0;
    int valc = 0;
    
    for (int i = 0; moves[i] != '\0'; i++) {
        switch(moves[i]) {
            case 'U': valh++; break;
            case 'D': valh--; break;
            case 'R': valc++; break;
            case 'L': valc--; break;
        }
    }
    
    return valh == 0 && valc == 0;
}