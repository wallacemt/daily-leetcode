#include <string.h>
#include <stdbool.h>

int countPalindromicSubsequence(char* s) {
    int n = strlen(s);
    int first[26], last[26];
    for (int i = 0; i < 26; ++i) { first[i] = -1; last[i] = -1; }

    for (int i = 0; i < n; ++i) {
        int c = s[i] - 'a';
        if (first[c] == -1) first[c] = i;
        last[c] = i;
    }

    int count = 0;
    for (int a = 0; a < 26; ++a) {
        if (first[a] == -1 || last[a] - first[a] < 2) continue;
        bool present[26] = { false };
        for (int k = first[a] + 1; k < last[a]; ++k)
            present[s[k] - 'a'] = true;
        for (int b = 0; b < 26; ++b)
            if (present[b]) ++count;
    }

    return count;
}
