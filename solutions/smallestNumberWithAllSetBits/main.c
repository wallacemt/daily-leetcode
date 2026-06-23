int smallestNumber(int n) {
    int bits = 0;
    int temp = n;
    while (temp > 0) {
        bits++;
        temp >>= 1;
    }
    int result = (1 << bits) - 1;
    if (result < n) {
        result = (1 << (bits + 1)) - 1;
    }
    
    return result;
}
