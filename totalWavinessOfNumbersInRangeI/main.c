int totalWaviness(int num1, int num2) {
    int total = 0;
    char n[12]; 
    int len;

    for (int num = num1; num <= num2; ++num) {
        int temp = num;
        len = 0;
        int tempCopy = num;
        
        while (tempCopy > 0) {
            len++;
            tempCopy /= 10;
        }
        
        if (len < 3) 
            continue;
        
        sprintf(n, "%d", num);
        
        for (int i = 1; i < len - 1; ++i) {
            char mid = n[i];
            char prev = n[i - 1];
            char next = n[i + 1];
            
            if ((mid > prev && mid > next) || 
                (mid < prev && mid < next)) {
                total++;
            }
        }
    }
    return total;
}