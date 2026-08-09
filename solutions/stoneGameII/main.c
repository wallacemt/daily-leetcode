#include <stdlib.h>
#include <limits.h>
#include <string.h>

static int max(int a, int b) {
    return a > b ? a : b;
}

static int solve(int index, int m, int n, int *suffix, int **memo) {
    if (index + 2 * m >= n)
        return suffix[index];

    int *memo_row = memo[index];
    
    if (memo_row[m] != -1)
        return memo_row[m];

    int opponent = INT_MAX;
    int limit = 2 * m;
    int max_x = (n - index < limit) ? (n - index) : limit;

    for (int x = 1; x <= max_x; x++) {
        int score = solve(index + x, max(m, x), n, suffix, memo);

        if (score < opponent)
            opponent = score;
    }

    return memo_row[m] = suffix[index] - opponent;
}

int stoneGameII(int *piles, int pilesSize) {
    int n = pilesSize;
    
    int *suffix = (int *)malloc((n + 1) * sizeof(int));
    suffix[n] = 0;

    for (int i = n - 1; i >= 0; i--)
        suffix[i] = suffix[i + 1] + piles[i];

    int **memo = (int **)malloc(n * sizeof(int *));
    
    for (int i = 0; i < n; i++) {
        memo[i] = (int *)malloc((n + 1) * sizeof(int));
        memset(memo[i], -1, (n + 1) * sizeof(int));
    }

    int result = solve(0, 1, n, suffix, memo);

    // Limpeza
    for (int i = 0; i < n; i++)
        free(memo[i]);
    free(memo);
    free(suffix);

    return result;
}