// Pré-calcula quais popcounts são primos (0-32 bits max para int)
static const bool PRIME_POPCOUNT[33] = {
    false, false, true,  true,  false, true,  false, true,
    false, false, false, true,  false, true,  false, false,
    false, true,  false, true,  false, false, false, true,
    false, false, false, false, false, true,  false, true,
    false
};

int countPrimeSetBits(int left, int right) {
    int res = 0;
    for (int i = left; i <= right; i++) {
        int bits = __builtin_popcount((unsigned)i);
        if (PRIME_POPCOUNT[bits]) {
            res++;
        }
    }
    return res;
}

static int popcount_fast(unsigned int x) {
    x -= (x >> 1) & 0x55555555;
    x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
    x = (x + (x >> 4)) & 0x0F0F0F0F;
    x += x >> 8;
    x += x >> 16;
    return x & 0x3F;
}

int countPrimeSetBits_Alt(int left, int right) {
    int res = 0;
    for (int i = left; i <= right; i++) {
        int bits = popcount_fast((unsigned)i);
        if (PRIME_POPCOUNT[bits]) {
            res++;
        }
    }
    return res;
}