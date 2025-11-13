#include <stdlib.h>
#include <string.h>
#include <stdint.h>

long long maxOperations(char* s) {
    int n = (int)strlen(s);
    int *pos = (int*)malloc(n * sizeof(int));
    if (!pos) return 0;
    int m = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '1') pos[m++] = i;
    }
    if (m == 0) { free(pos); return 0; }

    long long ans = 0;
    for (int k = 0; k < m - 1; ++k) {
        int gap = pos[k+1] - pos[k] - 1;
        if (gap > 0) ans += (long long)(k + 1);
    }
    int rightGap = (n - 1) - pos[m - 1];
    if (rightGap > 0) ans += (long long)m;

    free(pos);
    return ans;
}