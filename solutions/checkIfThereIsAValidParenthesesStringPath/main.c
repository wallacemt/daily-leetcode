#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

bool hasValidPath(char** grid, int gridSize, int* gridColSize) {
    int m = gridSize, n = gridColSize[0];
    int lim = (m + n) >> 1;
    int words = (lim + 64) / 64;
    
    // Validações iniciais
    if (((m + n) & 1) == 0 || grid[0][0] == ')' || grid[m-1][n-1] == '(')
        return false;
    
    // Alocação única e contígua
    uint64_t* data = (uint64_t*)calloc(m * n * words, sizeof(uint64_t));
    uint64_t** dp = (uint64_t**)malloc(n * sizeof(uint64_t*));
    for (int j = 0; j < n; j++)
        dp[j] = data + j * words;
    
    // Inicializar primeira célula
    dp[0][0] = 1ULL << 1;
    
    // Primeira linha
    int p = 1;
    for (int j = 1; j < n && p >= 0 && p <= lim; j++) {
        p += grid[0][j] == '(' ? 1 : -1;
        if (p >= 0 && p <= lim)
            dp[j][p >> 6] |= 1ULL << (p & 63);
    }
    
    // Processar linhas
    p = 1;
    for (int i = 1; i < m; i++) {
        p += grid[i][0] == '(' ? 1 : -1;
        
        // Verificar se dp[0] é alcançável
        bool reachable = false;
        for (int w = 0; w < words && !reachable; w++)
            reachable = dp[0][w] != 0;
        
        memset(dp[0], 0, words * sizeof(uint64_t));
        
        if (reachable && p >= 0 && p <= lim)
            dp[0][p >> 6] |= 1ULL << (p & 63);
        
        // Processar colunas
        for (int j = 1; j < n; j++) {
            // Mesclar com coluna anterior
            for (int w = 0; w < words; w++)
                dp[j][w] |= dp[j-1][w];
            
            // Shift baseado no caractere
            if (grid[i][j] == '(') {
                uint64_t carry = 0;
                for (int w = 0; w < words; w++) {
                    uint64_t next = dp[j][w] >> 63;
                    dp[j][w] = (dp[j][w] << 1) | carry;
                    carry = next;
                }
            } else {
                uint64_t carry = 0;
                for (int w = words - 1; w >= 0; w--) {
                    uint64_t next = dp[j][w] & 1;
                    dp[j][w] = (dp[j][w] >> 1) | (carry << 63);
                    carry = next;
                }
            }
             
            int validBits = (lim + 1) & 63;
            if (validBits)
                dp[j][words-1] &= (1ULL << validBits) - 1;
        }
    }
    
    bool result = dp[n-1][0] & 1ULL;
    
    free(dp);
    free(data);
    
    return result;
}