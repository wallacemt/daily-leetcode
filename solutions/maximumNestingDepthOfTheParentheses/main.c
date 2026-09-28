#include <string.h>
 
int maxDepth(char* s) {
    // Validação de entrada
    if (!s) {
        return -1;
    }

    int maxDepthVal = 0;
    int currentDepth = 0;

    // Processa cada caractere
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            currentDepth++;
 
            if (currentDepth > maxDepthVal) {
                maxDepthVal = currentDepth;
            }
        } else if (s[i] == ')') {
            currentDepth--;
 
            if (currentDepth < 0) {
                return -1; 
            }
        }
         
    }
 
    if (currentDepth > 0) {
        return -1;  
    }

    return maxDepthVal;
}