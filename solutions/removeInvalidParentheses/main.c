#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** data;
    int size;
    int capacity;
} StringArray;

void initArray(StringArray* arr) {
    arr->capacity = 16;
    arr->size = 0;
    arr->data = (char**)malloc(arr->capacity * sizeof(char*));
}

void addString(StringArray* arr, const char* str) {
    if (arr->size >= arr->capacity) {
        arr->capacity <<= 1;
        arr->data = (char**)realloc(arr->data, arr->capacity * sizeof(char*));
    }
    arr->data[arr->size++] = strdup(str);
}

void reverseString(char* str) {
    int left = 0, right = strlen(str) - 1;
    while (left < right) {
        char tmp = str[left];
        str[left] = str[right];
        str[right] = tmp;
        left++;
        right--;
    }
}

void constructValidExprs(char* expr, int readIdx, int removeIdx,
                         char open, char close, StringArray* results) {
    int balance = 0;
    int len = strlen(expr);
    
    // Encontra primeiro desequilíbrio
    for (int i = readIdx; i < len; i++) {
        balance += (expr[i] == open) ? 1 : (expr[i] == close) ? -1 : 0;
        
        if (balance >= 0) continue;
        
        // Remove um 'close' do prefixo desequilibrado
        for (int j = removeIdx; j <= i; j++) {
            if (expr[j] == close && (j == removeIdx || expr[j - 1] != close)) {
                char* next = (char*)malloc(len);
                memcpy(next, expr, j);
                strcpy(next + j, expr + j + 1);
                
                constructValidExprs(next, i, j, open, close, results);
                free(next);
            }
        }
        return;
    }
    
    // Se balanceado após primeira passagem
    if (balance == 0 && open == '(') {
        addString(results, expr);
        return;
    }
    
    // Segunda passagem: inverte e processa de trás para frente
    char* reversed = strdup(expr);
    reverseString(reversed);
    
    if (open == '(') {
        constructValidExprs(reversed, 0, 0, ')', '(', results);
    } else {
        addString(results, reversed);
    }
    free(reversed);
}

char** removeInvalidParentheses(char* s, int* returnSize) {
    StringArray results;
    initArray(&results);
    
    char* expr = strdup(s);
    constructValidExprs(expr, 0, 0, '(', ')', &results);
    free(expr);
    
    *returnSize = results.size;
    return results.data;
}