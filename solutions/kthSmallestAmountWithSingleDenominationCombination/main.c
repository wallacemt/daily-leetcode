#include <limits.h>

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// LCM com overflow protection
long long lcm_safe(long long a, long long b, long long max_val) {
    long long g = gcd(a, b);
    // Verifica overflow antes de multiplicar
    if (a / g > max_val / b) {
        return max_val + 1; // Retorna valor > max_val para indicar overflow
    }
    return (a / g) * b;
}

long long findKthSmallest(int* coins, int coinsSize, int k) {
    int n = coinsSize;
    int num_subsets = (1 << n) - 1;
    
    // Alocação dinâmica apenas do necessário
    long long* lcms = (long long*)malloc(num_subsets * sizeof(long long));
    int* signs = (int*)malloc(num_subsets * sizeof(int));
    
    long long min_coin = coins[0];
    int idx = 0;

    // Pré-computar LCMs e signs com inclusão-exclusão
    for (int i = 1; i < (1 << n); i++) {
        long long cur_lcm = 1;
        int bit_count = 0;
        long long max_lcm = (long long)min_coin * k;
        
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                bit_count++;
                long long coin = coins[j];
                if (coin < min_coin) min_coin = coin;
                
                // LCM com proteção contra overflow
                cur_lcm = lcm_safe(cur_lcm, coin, max_lcm);
                if (cur_lcm > max_lcm) break; // Early exit se overflow
            }
        }
        
        lcms[idx] = cur_lcm;
        signs[idx] = (bit_count & 1) ? 1 : -1; // Bit manipulation mais rápido
        idx++;
    }

    // Binary search otimizado
    long long left = 1;
    long long right = (long long)min_coin * k;

    while (left < right) {
        long long mid = left + (right - left) / 2;
        long long cnt = 0;
         
        for (int i = 0; i < num_subsets; i++) {
            if (lcms[i] <= mid) {
                cnt += signs[i] * (mid / lcms[i]);
            }
        }
        
        if (cnt >= k) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    free(lcms);
    free(signs);
    
    return left;
}