#include <stdbool.h>
 
bool checkString(char* s) {
    bool foundB = false;
    
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'b') {
            foundB = true;
        } else if (s[i] == 'a') { 
            if (foundB) {
                return false;
            }
        }
    }
    
    return true;
}