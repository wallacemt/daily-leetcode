#pragma optimize("O3, unroll-loops")
inline int mirrorDistance(int n) {
    long long rev = 0;
    for(int x = n; x; x /= 10) {
        rev = rev * 10 + x % 10;
    }
    return rev > n ? rev - n : n - rev;
}
