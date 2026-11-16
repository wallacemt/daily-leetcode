#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Calcula a soma dos dígitos em blocos de tamanho k até que |s| <= k.
 * Resolve o problema de memory leak e otimiza a alocação.
 */
char* digitSum(char* s, int k) {
    int n = strlen(s);
     
    char* current = strdup(s);
    
    while (n > k) { 
        char* next = (char*)malloc((n + 1) * sizeof(char));
        if (!next) return current;

        int next_pos = 0;

        for (int i = 0; i < n; i += k) {
            int sum = 0;
            for (int j = i; j < i + k && j < n; j++) {
                sum += current[j] - '0';
            }
             
            next_pos += sprintf(next + next_pos, "%d", sum);
        }

        next[next_pos] = '\0';
        
        free(current);  
        current = next;
        n = next_pos;
    }

    return current;
}