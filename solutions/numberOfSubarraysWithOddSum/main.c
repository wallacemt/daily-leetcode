#include <stdint.h>
 
int numOfSubarrays(int* arr, int arrSize) {
    const int MOD = 1000000007;
    
    long long odd_prefixes = 0;
    long long even_prefixes = 1; 
    long long current_sum = 0;
    long long result = 0;

    for (int i = 0; i < arrSize; i++) {
        current_sum += arr[i];
        
        if (current_sum % 2 != 0) { 
            result = (result + even_prefixes) % MOD;
            odd_prefixes++;
        } else { 
            result = (result + odd_prefixes) % MOD;
            even_prefixes++;
        }
    }

    return (int)result;
}