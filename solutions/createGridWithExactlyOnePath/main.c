#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** createGrid(int m, int n, int* returnSize) { 
    char** ans = (char**)malloc(m * sizeof(char*));
 
    ans[0] = (char*)malloc((n + 1) * sizeof(char)); // +1 para o caractere nulo
    memset(ans[0], '.', n);
    ans[0][n] = '\0'; // Adiciona o caractere nulo no final
 
    for (int i = 1; i < m; i++) {
        ans[i] = (char*)malloc((n + 1) * sizeof(char)); // +1 para o caractere nulo
        memset(ans[i], '#', n - 1); // Preenche com hashes (#)
        ans[i][n - 1] = '.'; // Última coluna com ponto (.)
        ans[i][n] = '\0'; // Adiciona o caractere nulo no final
    }

    *returnSize = m;  
    return ans; 
}

 