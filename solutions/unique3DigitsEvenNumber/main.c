#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isEven(int n) {
    return n % 2 == 0;
}

int totalNumbers(int* digits, int digitsSize) {
    if (digitsSize < 3) return 0;   
    
    int count = 0;
    bool used[1000] = {false};   
     
    for (int i = 0; i < digitsSize; i++) {
        if (digits[i] == 0) continue;
         
        for (int j = 0; j < digitsSize; j++) {
            if (i == j) continue;  // Não reutiliza índice
             
            for (int k = 0; k < digitsSize; k++) {
                if (k == i || k == j) continue;  // Não reutiliza índice
                if (!isEven(digits[k])) continue;  // Deve ser par
                
                int number = digits[i] * 100 + digits[j] * 10 + digits[k];
                 
                if (!used[number]) {
                    used[number] = true;
                    count++;
                }
            }
        }
    }
    
    return count;
}