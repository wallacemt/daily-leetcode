#include <limits.h>

long long countCommas(long long n) {
    long long total_commas = 0;
    long long threshold = 1000;
    
    while (n >= threshold) {
        total_commas += (n - threshold + 1);
        
      
        if (threshold > LLONG_MAX / 1000) {
            break;
        }
        threshold *= 1000;
    }
    
    return total_commas;
}