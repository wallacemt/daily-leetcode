int countCommas(int n) {
    if (n < 1000) return 0;
    
    long long total = 0; 
    if (n >= 1000) {
        total += (long long)fmin(n, 999999) - 999;
    }
     
    if (n >= 1000000) {
        total += 2LL * ((long long)fmin(n, 999999999) - 999999);
    }
     
    if (n >= 1000000000) {
        total += 3LL * ((long long)n - 999999999);
    }
    
    return (int)total;
}