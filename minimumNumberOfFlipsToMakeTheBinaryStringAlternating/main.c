int minFlips(const char *const s) {
    uint n = 0, k = 0;
    for (char c = *s; c; c = s[++n])
        k += (n ^ c) & 1;
    uint r = MIN(k, n - k);
    if (n & 1) {
        uint i = 0;
        for (char c = *s; c; c = s[++i]) {
            k += ((i ^ c ^ 1) & 1) - ((i ^ c) & 1);
            r = MIN(r, MIN(k, n - k));
        }
    }
    return r;
}
