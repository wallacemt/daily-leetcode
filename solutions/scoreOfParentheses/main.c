#include <stddef.h>

int scoreOfParentheses(const char* s) {
    int depth = 0;
    unsigned int score = 0;

    for (int i = 0; s[i]; ++i) {
        if (s[i] == '(') {
            ++depth;
        } else {
            --depth;
            if (s[i - 1] == '(') {
                score += 1U << depth;
            }
        }
    }

    return (int)score;
}