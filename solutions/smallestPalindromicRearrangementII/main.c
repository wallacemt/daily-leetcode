typedef unsigned long long ull;
static const ull LIMIT = 1000001ULL;   // k <= 1e6, cap counts here

static ull binom_cap(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r > n - r) r = n - r;
    ull res = 1;
    for (int i = 1; i <= r; i++) {
        __int128 t = (__int128)res * (n - r + i) / i;
        if (t >= (__int128)LIMIT) return LIMIT;
        res = (ull)t;
    }
    return res;
}

// distinct permutations of the multiset cnt[], capped at LIMIT
static ull perms_cap(int *cnt) {
    int rem = 0;
    for (int i = 0; i < 26; i++) rem += cnt[i];
    ull res = 1;
    for (int i = 0; i < 26; i++) {
        if (!cnt[i]) continue;
        __int128 t = (__int128)res * binom_cap(rem, cnt[i]);
        if (t >= (__int128)LIMIT) return LIMIT;
        res = (ull)t;
        rem -= cnt[i];
    }
    return res;
}

char* smallestPalindrome(char* s, int k) {
    int n = strlen(s), cnt[26] = {0}, mid = -1;
    for (int i = 0; i < n; i++) cnt[s[i] - 'a']++;
    for (int i = 0; i < 26; i++) { if (cnt[i] & 1) mid = i; cnt[i] /= 2; }

    int h = n / 2;
    char *res = malloc(n + 1);
    res[n] = '\0';
    if (mid >= 0) res[h] = 'a' + mid;

    if ((ull)k > perms_cap(cnt)) { res[0] = '\0'; return res; }

    ull kk = k;
    for (int pos = 0; pos < h; pos++)
        for (int c = 0; c < 26; c++) {
            if (!cnt[c]) continue;
            cnt[c]--;
            ull ways = perms_cap(cnt);
            if (kk > ways) { kk -= ways; cnt[c]++; }
            else { res[pos] = res[n - 1 - pos] = 'a' + c; break; }
        }
    return res;
}