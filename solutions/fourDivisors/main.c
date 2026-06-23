#include <math.h>
#include <string.h>

int isPrime(int x) {
    if (x < 2) return 0;
    if (x == 2) return 1;
    if (x % 2 == 0) return 0;
    if (x == 3) return 1;
    if (x % 3 == 0) return 0;
    
    for (int i = 5; i * i <= x; i += 6) {
        if (x % i == 0 || x % (i + 2) == 0) return 0;
    }
    return 1;
}

int sumOne(int n) {
    int p = (int) round(cbrt(n));
    
    // Verifica p-1, p, p+1 para evitar erros de arredondamento
    for (int candidate = p - 1; candidate <= p + 1; candidate++) {
        if (candidate > 1) {
            long cube = (long)candidate * candidate * candidate;
            if (cube == n && isPrime(candidate)) {
                return 1 + candidate + candidate * candidate + n;
            }
        }
    }

    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            int a = i;
            int b = n / i;
            
            // Verifica se são primos distintos
            if (a != b && isPrime(a) && isPrime(b)) {
                return 1 + a + b + n;
            }
            return -1;
        }
    }
    
    return -1;
}

int sumFourDivisors(int* nums, int numsSize) {
    int res = 0;
    for (int i = 0; i < numsSize; i++) {
        int val = sumOne(nums[i]);
        if (val != -1) res += val;
    }
    return res;
}