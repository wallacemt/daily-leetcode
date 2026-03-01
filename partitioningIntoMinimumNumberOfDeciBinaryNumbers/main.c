int minPartitions(char* n) {
    if (!n) return 0;
    
    int maxDigit = 0;
    
    // Uma única passagem pela string
    for (int i = 0; n[i]; i++) {
        int digit = n[i] - '0';
        if (digit > maxDigit) {
            maxDigit = digit;
            if (maxDigit == 9) return 9; // Early exit
        }
    }
    
    return maxDigit;
}
