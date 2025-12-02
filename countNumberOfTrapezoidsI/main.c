int cmp(const void* a, const void* b) {
    return (*(int*)a - *(int*)b); 
}

int countTrapezoids(int** points, int pointsSize, int* pointsColSize) {
    const long long mod = 1e9 + 7;
    int* y = (int*) malloc(pointsSize * sizeof(int));

    for (int i = 0; i < pointsSize; i++) {
        y[i] = points[i][1];
    }
    
    qsort(y, pointsSize, sizeof(int), cmp);
    
    long long sum = 0, pairs = 0;
    int f = 1;
    
    for (int i = 1; i < pointsSize; i++) {
        if (y[i] == y[i-1]) {
            f++;
        } else {
            long long pair = (long long)f * (f - 1) / 2;
            sum += pair;
            pairs += pair * pair;
            f = 1;
        }
    }
    
    long long pair = (long long)f * (f - 1) / 2;
    sum += pair;
    pairs += pair * pair;
    
    long long result = (sum * sum - pairs) / 2 % mod;
    free(y);
    
    return result;
}