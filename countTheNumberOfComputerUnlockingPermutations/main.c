#define MOD 1000000007

int countPermutations(int* complexity, int complexitySize) {
    if (complexitySize <= 1) return 1;
    
    int first = complexity[0];
    
    for (int i = 1; i < complexitySize; i++) {
        if (complexity[i] <= first) return 0;
    }
    
    if (complexitySize <= 13) {
        static const int factorials[] = {
            1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880, 
            3628800, 39916800, 479001600
        };
        return factorials[complexitySize - 1];
    }
    
    long long fact = 479001600; // 12!
    for (int i = 13; i < complexitySize; i++) {
        fact = (fact * i) % MOD;
    }
    
    return (int)fact;
}