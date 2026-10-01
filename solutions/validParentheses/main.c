#include <stdbool.h>
#include <string.h>

bool isValid(char* s) {
    char stack[10000];
    int top = -1;
    
    for (int i = 0; s[i]; i++) {
        char c = s[i];
        
        if (c == '(' || c == '[' || c == '{') {
            stack[++top] = c;
        } else if (top >= 0 && stack[top] == c - 1) {
            top--;
        } else if (top >= 0 && stack[top] == c - 2) {
            top--;
        } else {
            return false;
        }
    }
    
    return top == -1;
}