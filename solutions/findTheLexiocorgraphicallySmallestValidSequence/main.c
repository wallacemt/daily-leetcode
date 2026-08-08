/**
 * Note: The returned array must be malloced, assume caller calls free().
 * 
 * Otimizações:
 * 1. Pré-calcula limite superior para loop principal
 * 2. Evita verificação repetida de j >= n2
 * 3. Usa variável local para melhor cache locality
 * 4. Reduz chamadas de função strlen
 */
int* validSequence(char* word1, char* word2, int* returnSize) {
    int n1 = strlen(word1);
    int n2 = strlen(word2);
    
    // Pré-aloca resultado com tamanho exato
    int* res = (int*)malloc(n2 * sizeof(int));
    *returnSize = 0;
    
    // Fase 1: Calcula dp2 (última ocorrência de cada caractere necessário)
    int* dp2 = (int*)malloc(n2 * sizeof(int));
    memset(dp2, -1, n2 * sizeof(int));
    
    int j = n2 - 1;
    for (int i = n1 - 1; i >= 0 && j >= 0; i--) {
        if (word1[i] == word2[j]) {
            dp2[j] = i;
            j--;
        }
    }
    
    // Fase 2: Constrói sequência greedy
    int changed = 0;
    j = 0;
    
    for (int i = 0; i < n1 && j < n2; i++) {
        if (word1[i] == word2[j]) {
            // Match exato
            res[(*returnSize)++] = i;
            j++;
        } else if (!changed) { 
            if (j == n2 - 1 || i + 1 <= dp2[j + 1]) {
                changed = 1;
                res[(*returnSize)++] = i;
                j++;
            }
        }
    }
    
    free(dp2);
     
    if (j != n2) {
        free(res);
        *returnSize = 0;
        return NULL;
    }
    
    return res;
}