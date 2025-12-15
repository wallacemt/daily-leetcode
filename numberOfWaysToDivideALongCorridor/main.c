#define MOD 1000000007

int numberOfWays(char* corridor) {
    int seatCount = 0;
    long long result = 1;
    int plantsBetween = 0;
    
    for (int i = 0; corridor[i] != '\0'; i++) {
        if (corridor[i] == 'S') seatCount++;
    }
    
    if (seatCount == 0 || seatCount % 2 != 0) return 0;
    
    seatCount = 0;
    for (int i = 0; corridor[i] != '\0'; i++) {
        if (corridor[i] == 'S') {
            seatCount++;
            if (seatCount > 2 && seatCount % 2 == 1) {
                result = (result * (plantsBetween + 1)) % MOD;
            }
            plantsBetween = 0;
        } else if (seatCount > 0 && seatCount % 2 == 0) {
            plantsBetween++;
        }
    }
    
    return result;
}