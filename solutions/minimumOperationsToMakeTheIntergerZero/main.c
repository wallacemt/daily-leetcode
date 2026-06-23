int makeTheIntegerZero(int num1, int num2) {
    for (int k = 1; k <= 60; k++) {
        long long remaining = (long long)num1 - (long long)k * num2; 
       if (remaining > 0 && __builtin_popcountll(remaining) <= k && remaining >= k) {
            return k;
        }
    }
    return -1;
}
