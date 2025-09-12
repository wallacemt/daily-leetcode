#include <string.h>
#include <stdbool.h>

bool doesAliceWin(char* s) {
    int len = strlen(s);
    
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            return true;
        }
    }
    return false;
}
