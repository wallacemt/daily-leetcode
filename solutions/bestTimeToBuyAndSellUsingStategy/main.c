long long maxProfit(int* prices, int pricesSize, int* strategy, int strategySize, int k) {
    int n = pricesSize, h = k >> 1;
    long long base = 0, prev = 0, nxt = 0, best = 0;
    
    // Pre-compute strategy * prices to avoid repeated multiplications
    long long* stratPrices = (long long*)malloc(n * sizeof(long long));
    
    for (int i = 0; i < n; i++) {
        stratPrices[i] = (long long)strategy[i] * prices[i];
        base += stratPrices[i];
    }

    for (int i = 0; i < k; i++) {
        prev += stratPrices[i];
        if (i >= h) nxt += prices[i];
    }

    best = nxt > prev ? nxt - prev : 0;

    for (int r = k; r < n; r++) {
        int l = r - k + 1;
        prev += stratPrices[r] - stratPrices[l - 1];
        nxt += prices[r] - prices[l - 1 + h];
        long long diff = nxt - prev;
        if (diff > best) best = diff;
    }
    
    free(stratPrices);
    return base + best;
}