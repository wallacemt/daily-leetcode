#include <stdbool.h>
#include <string.h>

bool hasSameDigits(char* s) {
    if (!s) return false;
    size_t n = strlen(s);
    while (n > 2) {
        for (size_t i = 0; i + 1 < n; ++i) {
            int a = s[i] - '0';
            int b = s[i+1] - '0';
            s[i] = (char)(((a + b) % 10) + '0');
        }
        --n;
        s[n] = '\0';
    }
    return n == 2 && s[0] == s[1];
}
