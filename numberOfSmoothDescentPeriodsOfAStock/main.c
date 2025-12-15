long long getDescentPeriods(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;
    
    long long total = 0;
    int length = 1;
    
    for (int i = 0; i < pricesSize; i++) {
        if (i > 0 && prices[i] == prices[i-1] - 1) {
            length++;
        } else {
            length = 1;
        }
        total += length;
    }
    
    return total;
}