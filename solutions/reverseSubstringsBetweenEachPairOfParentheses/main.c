#include <stdlib.h>
#include <string.h>

/**
 * Inverte conteúdo entre parênteses e remove os parênteses.
 * 
 * @param s String com parênteses
 * @return String processada, ou NULL se erro
 * 
 * Exemplo: "a(bc)de" → "acbde"
 */
char* reverseParentheses(char* s) {
    // Validação de entrada
    if (!s) {
        return NULL;
    }

    int n = strlen(s);
 
    char* stack = (char*)malloc((n + 1) * sizeof(char));
    if (!stack) {
        return NULL;
    }

    int top = 0;
 
    for (int i = 0; i < n; i++) {
        if (s[i] == ')') {
            // Encontra '(' correspondente
            int j = top - 1;
            while (j >= 0 && stack[j] != '(') {
                j--;
            }
 
            if (j < 0) {
                free(stack);
                return NULL;  // Parêntese desbalanceado
            }
 
            int left = j + 1;
            int right = top - 1;
            while (left < right) {
                char temp = stack[left];
                stack[left] = stack[right];
                stack[right] = temp;
                left++;
                right--;
            }
 
            for (int k = j; k < top - 1; k++) {
                stack[k] = stack[k + 1];
            }
            top--;
        } else if (s[i] == '(') { 
            stack[top++] = s[i];
        } else { 
            stack[top++] = s[i];
        }
    }
 
    for (int i = 0; i < top; i++) {
        if (stack[i] == '(') {
            free(stack);
            return NULL;  // Parêntese não fechado
        }
    }

    stack[top] = '\0';
    return stack;
}