int stoneGameVIII(int* stones, int stonesSize) {
    long long prefix = 0;

    for (int i = 0; i < stonesSize; ++i) {
        prefix += stones[i];
    }

    long long best = prefix;

    for (int i = stonesSize - 2; i >= 1; --i) {
        prefix -= stones[i + 1];

        long long candidate = prefix - best;

        if (candidate > best) {
            best = candidate;
        }
    }

    return (int)best;
}
