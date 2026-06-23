int bitwiseComplement(int n) {
    if (n == 0) return 1;
    return n ^ ((1 << (32 - __builtin_clz(n))) - 1);
}
