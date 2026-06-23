int concatenatedBinary(int n) {
    const int MOD = 1000000007;
    int bitLength = 1;      // Número de bits do número atual
    int lastPowerOfTwo = 1; // Último número onde incrementamos bitLength
    long long result = 0;
    
    for (int num = 1; num <= n; num++) {
        if (lastPowerOfTwo * 2 == num) {
            bitLength++;
            lastPowerOfTwo = num;
        }
        result = ((result << bitLength) | num) % MOD;
    }
    
    return (int)result;
}