bool stoneGameIX(int* stones, int stonesSize) {
    int count[3] = {0, 0, 0};
 
    for (int i = 0; i < stonesSize; ++i) {
        count[stones[i] % 3]++;
    }
 
    if (count[0] % 2 == 0) {
        return count[1] > 0 && count[2] > 0;
    }
 
    return (count[1] - count[2] >= 3) || (count[2] - count[1] >= 3);
}