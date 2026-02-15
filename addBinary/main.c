#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char* addBinary(char* a, char* b) {
    if (!a || !b) return NULL;
    
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxLen = (lenA > lenB) ? lenA : lenB;
    
    char* result = (char*)malloc(maxLen + 2);
    if (!result) return NULL;
    
    int carry = 0;
    int pos = maxLen; 
    
    for (int i = 0; i < maxLen; i++) {
        int bitA = (i < lenA) ? a[lenA - 1 - i] - '0' : 0;
        int bitB = (i < lenB) ? b[lenB - 1 - i] - '0' : 0;
        
        int sum = bitA + bitB + carry;
        result[pos--] = (sum % 2) + '0';
        carry = sum / 2;
    }
    
    if (carry) {
        result[pos] = '1';
    } else {
        pos++;
    }
    
    result[maxLen + 1] = '\0';
    
    return result + pos;
}

