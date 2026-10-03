#include <string.h>
#include <stdlib.h>

int longestValidParentheses(char* s) {
    int n = strlen(s);
    int* stack = (int*)malloc((n + 1) * sizeof(int));
    int top = 0;
    int max_len = 0;
    
    stack[0] = -1;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            stack[++top] = i;
        } else {
            if (--top < 0) {
                top = 0;
                stack[0] = i;
            } else {
                int len = i - stack[top];
                if (len > max_len)
                    max_len = len;
            }
        }
    }

    free(stack);
    return max_len;
}