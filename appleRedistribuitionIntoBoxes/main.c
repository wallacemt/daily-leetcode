
int minimumBoxes(int* apple, int n, int* capacity, int m) {

    int totalApples = 0;
    for(int i = 0; i < n; i++) {
        totalApples += apple[i];
    }
    
    uint8_t freq[51] = {0};
    int maxCapacity = 0;
    for(int i = 0; i < m; i++) {
        int cap = capacity[i];
        freq[cap]++;
        if(cap > maxCapacity) maxCapacity = cap;
    }
    
    int boxesUsed = 0;
    for(int cap = maxCapacity; cap > 0 && totalApples > 0; cap--) {
        if(freq[cap] == 0) continue;
        
        int canStore = (long long)cap * freq[cap];
        
        if(canStore >= totalApples) {
            return boxesUsed + (totalApples + cap - 1) / cap;
        }
        
        totalApples -= canStore;
        boxesUsed += freq[cap];
    }
    
    return -1;
}