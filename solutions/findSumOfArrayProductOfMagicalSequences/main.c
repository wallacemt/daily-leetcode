#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD 1000000007
#define MAX_M 30
#define MAX_K 30
#define MAX_N 50

static long long C[MAX_M + 1][MAX_M + 1];
static long long memo[MAX_N + 1][MAX_M + 1][MAX_K + 1][MAX_M + 1];
static int memo_initialized = 0;

static void precompute_binomial_coefficients(int max_m) {
    memset(C, 0, sizeof(C));
    
    for (int i = 0; i <= max_m; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % MOD;
        }
    }
}

static long long mod_power(long long base, long long exp) {
    if (exp == 0) return 1;
    
    long long result = 1;
    base %= MOD;
    
    while (exp > 0) {
        if (exp & 1) {
            result = (result * base) % MOD;
        }
        base = (base * base) % MOD;
        exp >>= 1;
    }
    
    return result;
}

static long long dp_solve(const int* nums, int n, int m, int pos, 
                         int remaining_selections, int remaining_bits, int carry) {
    
    if (remaining_bits < 0 || remaining_selections < 0 || carry > m) {
        return 0;
    }
    
    if (pos == n) {
        return (remaining_selections == 0 && remaining_bits == __builtin_popcount(carry)) ? 1 : 0;
    }
    
    if (memo[pos][remaining_selections][remaining_bits][carry] != -1) {
        return memo[pos][remaining_selections][remaining_bits][carry];
    }
    
    long long result = 0;
    
    for (int select = 0; select <= remaining_selections; select++) {
        int new_sum = carry + select;
        int new_remaining_bits = remaining_bits - (new_sum & 1);
        int new_carry = new_sum >> 1;
        
        if (new_remaining_bits >= 0) {
            long long combinations = C[remaining_selections][select];
            long long power_contribution = mod_power(nums[pos], select);
            long long sub_result = dp_solve(nums, n, m, pos + 1, 
                                          remaining_selections - select, 
                                          new_remaining_bits, new_carry);
            
            result = (result + (combinations * power_contribution % MOD * sub_result % MOD)) % MOD;
        }
    }
    
    return memo[pos][remaining_selections][remaining_bits][carry] = result;
}

int magicalSum(int m, int k, int* nums, int numsSize) {
    if (!nums || numsSize <= 0 || m <= 0 || k < 0 || m > MAX_M || k > MAX_K || numsSize > MAX_N) {
        return 0;
    }
    
    memset(memo, -1, sizeof(memo));
    
    precompute_binomial_coefficients(m);
    
    return (int)dp_solve(nums, numsSize, m, 0, m, k, 0);
}

