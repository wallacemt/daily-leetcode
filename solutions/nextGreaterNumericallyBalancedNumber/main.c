int nextBeautifulNumber(int n) {
    for (int cand = n + 1; ; ++cand) {
        int x = cand;
        int cnt[10] = {0};
        while (x > 0) {
            cnt[x % 10]++;
            x /= 10;
        }
        if (cnt[0] > 0) continue; 
        int ok = 1;
        for (int d = 1; d <= 9; ++d) {
            if (cnt[d] != 0 && cnt[d] != d) { ok = 0; break; }
        }
        if (ok) return cand;
    }
}
