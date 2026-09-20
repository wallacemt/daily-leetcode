#include <string.h>
 
static inline long long reverseDegree(const char* s) {
    long long total = 0;
     
    for (int i = 0; s[i]; i++) { 
        int revAlpha = 26 - (s[i] - 'a');
        total += (long long)revAlpha * (i + 1);
    }

    return total;
}