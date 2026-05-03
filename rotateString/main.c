#include <string.h>

bool rotateString(char* s, char* goal) {
    int n = strlen(s);
    if (n != strlen(goal)) 
        return false;
    
    if (n == 0) return true;
    
    char* doubled = (char*)malloc(2 * n + 1);
    if (!doubled) return false;
    
    strcpy(doubled, s);
    strcat(doubled, s);
    
    bool result = strstr(doubled, goal) != NULL;
    free(doubled);
    
    return result;
}
