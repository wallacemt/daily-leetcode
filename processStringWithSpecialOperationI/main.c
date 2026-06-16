#include <stdlib.h>
#include <string.h>

#define MAXR  (1<<20)   

char* processStr(char* s) {
    static char result[MAXR];
    int len = 0;

    for (int i = 0; s[i]; ++i) {
        char ch = s[i];

        if (ch >= 'a' && ch <= 'z') {
            result[len++] = ch;
        }
        else if (ch == '*') {
            if (len > 0) --len;
        }
        else if (ch == '#') {
            if (len > 0) {
         
                memcpy(result + len, result, len);
                len <<= 1;  // len *= 2
            }
        }
        else if (ch == '%') {
        
            for (int l = 0, r = len - 1; l < r; ++l, --r) {
                char tmp = result[l];
                result[l] = result[r];
                result[r] = tmp;
            }
        }
    }

    result[len] = '\0';
    return result;
}