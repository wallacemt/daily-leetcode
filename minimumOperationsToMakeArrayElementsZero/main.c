long long minOperations(int** queries, int queriesSize, int* queriesColSize) {
    long long res = 0;
    
    for (int i = 0; i < queriesSize; i++) {
        long long l = queries[i][0], r = queries[i][1];
        long long operations = 0;
        
        for (int power = 0; power < 32; power++) {
            long long powerOf4 = 1LL << (2 * power); 
            long long nextPowerOf4 = 1LL << (2 * (power + 1)); 
            
            if (powerOf4 > r) break;
            
            long long left = (l > powerOf4) ? l : powerOf4;
            long long right = (r < nextPowerOf4 - 1) ? r : nextPowerOf4 - 1;
            
            if (left <= right) {
                operations += (right - left + 1) * (power + 1);
            }
        }
        
        res += (operations + 1) / 2;
    }
    
    return res;
}
