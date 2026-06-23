int numWaterBottles(int numBottles, int numExchange) {  
    int ans = numBottles;
    int empty = numBottles;
    
    while(empty >= numExchange){
        int newFull = empty / numExchange;
        ans += newFull;
        empty = empty % numExchange + newFull;
    }
    
    return ans;   
}