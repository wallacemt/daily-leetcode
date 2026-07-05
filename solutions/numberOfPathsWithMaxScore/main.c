/**
 * Note: The returned array must be malloced, assume caller calls free().
 * Optimized version: O(n²) time, O(n) space with single allocation
 */
int* pathsWithMaxScore(char** board, int boardSize, int* returnSize) {
    if (!board || boardSize <= 0 || !returnSize) {
        int* ans = malloc(2 * sizeof(int));
        ans[0] = 0;
        ans[1] = 0;
        *returnSize = 2;
        return ans;
    }

    const int MOD = 1000000007;
    const int n = boardSize;
    const int INVALID = -1;
 
    int* score = (int*)malloc(n * sizeof(int));
    int* ways = (int*)malloc(n * sizeof(int));
    int* tempScore = (int*)malloc(n * sizeof(int));
    int* tempWays = (int*)malloc(n * sizeof(int));
 
    memset(score, INVALID, n * sizeof(int));
    memset(ways, 0, n * sizeof(int));

    for (int r = n - 1; r >= 0; r--) {
        memset(tempScore, INVALID, n * sizeof(int));
        memset(tempWays, 0, n * sizeof(int));

        for (int c = n - 1; c >= 0; c--) {
            char cell = board[r][c];
 
            if (cell == 'X') continue;

            if (cell == 'S') {
                tempScore[c] = 0;
                tempWays[c] = 1;
                continue;
            }
 
            int best = INVALID;
            int rightScore = (c + 1 < n) ? tempScore[c + 1] : INVALID;
            int downScore = score[c];
            int diagScore = (c + 1 < n) ? score[c + 1] : INVALID;
 
            if (rightScore > best) best = rightScore;
            if (downScore > best) best = downScore;
            if (diagScore > best) best = diagScore;

            if (best == INVALID) continue;
 
            long long cnt = 0;
            if (rightScore == best) cnt += tempWays[c + 1];
            if (downScore == best) cnt += ways[c];
            if (diagScore == best) cnt += ways[c + 1];
 
            int val = (cell == 'E') ? 0 : (cell - '0');

            tempScore[c] = best + val;
            tempWays[c] = (int)(cnt % MOD);
        }
 
        int* tmp = score;
        score = tempScore;
        tempScore = tmp;

        tmp = ways;
        ways = tempWays;
        tempWays = tmp;
    }

    // Preparação do resultado
    int* ans = (int*)malloc(2 * sizeof(int));
    *returnSize = 2;

    if (score[0] == INVALID) {
        ans[0] = 0;
        ans[1] = 0;
    } else {
        ans[0] = score[0];
        ans[1] = ways[0];
    }

    // Limpeza
    free(score);
    free(ways);
    free(tempScore);
    free(tempWays);

    return ans;
}