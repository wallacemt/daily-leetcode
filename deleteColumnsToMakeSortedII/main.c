#include <string.h>

int minDeletionSize(char** strs, int strsSize) {
    if (strsSize <= 1) return 0;
    
    int m = strlen(strs[0]);
    int sorted[strsSize - 1];

    for (int i = 0; i < strsSize - 1; i++) {
        sorted[i] = 0;
    }
    
    int deletions = 0;
    for (int c = 0; c < m; c++) {
        int bad = 0;
        for (int i = 0; i < strsSize - 1; i++) {
            if (sorted[i]) continue;

            if (strs[i][c] > strs[i + 1][c]) {
                bad = 1;
                break;
            }
        }

        if (bad) {
            deletions++;
            continue;
        }
        for (int i = 0; i < strsSize - 1; i++) {
            if (sorted[i]) continue;

            if (strs[i][c] < strs[i + 1][c]) {
                sorted[i] = 1;
            }
        }
    }
    return deletions;
}