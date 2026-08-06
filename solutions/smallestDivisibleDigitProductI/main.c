#include <stdio.h>
 
int digitProduct(int n) {
    int product = 1;
    while (n > 0) {
        int digit = n % 10;
        product *= digit; 
        if (product == 0) return 0;
        n /= 10;
    }
    return product;
}

int smallestNumber(int n, int t) {
  
    int product = digitProduct(n);
    
    while (1) {
        if (product % t == 0) {
            return n;
        }
        
        n++;
        product = digitProduct(n);
    }
}
 
