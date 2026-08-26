#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* shortestBeautifulSubstring(char* s, int k) {
    if (s == NULL) {
        return NULL;
    }

    size_t n = strlen(s);

    /*
     * Aloca sempre n + 1 bytes para permitir devolver
     * uma string vazia quando não existe solução.
     */
    char* ans = malloc((n + 1) * sizeof(*ans));

    if (ans == NULL) {
        return NULL;
    }

    ans[0] = '\0';

    /*
     * Não existe uma substring válida para k <= 0.
     */
    if (k <= 0) {
        return ans;
    }

    size_t left = 0;
    size_t ones = 0;

    size_t best_start = 0;
    size_t best_len = 0;

    for (size_t right = 0; right < n; right++) {
        if (s[right] == '1') {
            ones++;
        }

      
        while (ones == (size_t)k) {
             
            while (left <= right && s[left] == '0') {
                left++;
            }

            size_t current_len = right - left + 1;

            int is_better = 0;

            if (best_len == 0) {
                is_better = 1;
            } else if (current_len < best_len) {
                is_better = 1;
            } else if (
                current_len == best_len &&
                memcmp(
                    s + left,
                    s + best_start,
                    current_len
                ) < 0
            ) { 
                is_better = 1;
            }

            if (is_better) {
                best_start = left;
                best_len = current_len;
            }

            /*
             * Remove o primeiro '1' da janela.
             */
            ones--;
            left++;
        }
    }
 
    if (best_len > 0) {
        memcpy(ans, s + best_start, best_len);
        ans[best_len] = '\0';
    }

    return ans;
}
