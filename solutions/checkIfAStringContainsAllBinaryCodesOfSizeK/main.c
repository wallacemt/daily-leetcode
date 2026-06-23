#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

bool hasAllCodes(char* s, int k) {
    if (s == NULL || k <= 0 || k > 30)
        return false;

    int n = strlen(s);
    const int total_codes = 1 << k;  
    const int mask = total_codes - 1;

    if (total_codes > n - k + 1)
        return false;

    for (int i = 0; i < n; i++) {
        if (s[i] != '0' && s[i] != '1')
            return false;
    }

    bool* seen = (bool*) calloc(total_codes, sizeof(bool));
    if (seen == NULL)
        return false;

    int code = 0;
    int found = 0;

    for (int i = 0; i < n; i++) {
        code = ((code << 1) & mask) | (s[i] == '1');

        if (i >= k - 1 && !seen[code]) {
            seen[code] = true;
            found++;

            if (found == total_codes) {
                free(seen);
                return true;
            }
        }
    }

    free(seen);
    return false;
}