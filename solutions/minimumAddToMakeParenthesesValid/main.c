#include <string.h>

int minAddToMakeValid(char* s) {
    int open = 0, close = 0;

    for (int i = 0; s[i]; i++) {
        if (s[i] == '(') {
            open++;
        } else if (open > 0) {
            open--;
        } else {
            close++;
        }
    }
    
    return open + close;
}