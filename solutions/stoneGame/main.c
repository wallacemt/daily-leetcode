bool stoneGame(int* piles, int pilesSize) {
    int n = pilesSize;
    
    // dp[i][j] = máxima diferença (meu score - oponente) 
    // quando jogador atual joga no intervalo [i, j]
    int* dp = (int*)calloc(n * n, sizeof(int));
    
    // Otimização 1: Pré-calcular somas de prefixo
    int* prefix = (int*)calloc(n + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        prefix[i + 1] = prefix[i] + piles[i];
    }
    
    // Preenchimento: começar com intervalos pequenos
    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            
            if (len == 1) {
                // Apenas uma pilha: pego ela
                dp[i * n + j] = piles[i];
            } else {
                // Pego pilha[i]: ganho piles[i], oponente joga em [i+1, j]
                int takeLeft = piles[i] - dp[(i + 1) * n + j];
                
                // Pego pilha[j]: ganho piles[j], oponente joga em [i, j-1]
                int takeRight = piles[j] - dp[i * n + (j - 1)];
                
                // Escolho a opção que maximiza minha diferença
                dp[i * n + j] = takeLeft > takeRight ? takeLeft : takeRight;
            }
        }
    }
    
    int result = dp[0 * n + (n - 1)] > 0;
    
    free(dp);
    free(prefix);
    
    return result;
}