#include <stdio.h>

long long sumAndMultiply(int n) {
    if (n == 0) return 0;
    long long sum = 0;
    long long multiplied = 0;
    int temp = n;
    
    while (temp > 0) {
        int digit = temp % 10;
        if (digit != 0) {
            sum += digit;
            multiplied = multiplied * 10 + digit;
        }
        temp /= 10;
    }
    
    if (multiplied == 0) return 0;
    
    long long result = 0;
    while (multiplied > 0) {
        result = result * 10 + (multiplied % 10);
        multiplied /= 10;
    }
    
    return result * sum;
}