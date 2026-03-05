#include <string.h>
#include <stdio.h>

int minOperations(char* s) {
    int n = strlen(s);
    int count = 0;

    for(int i = 0; i < n; i++) {
        if((s[i] - '0') == (i & 1)) {
            count++;
        }
    }
    
    return (count < n - count) ? count : n - count;
}

