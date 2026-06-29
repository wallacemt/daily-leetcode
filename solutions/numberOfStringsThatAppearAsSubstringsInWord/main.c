#include <string.h>
#include <stddef.h>

int numOfStrings(char **patterns, int patternsSize, char *word) {
    // Validações
    if (!patterns || !word || patternsSize <= 0) {
        return 0;
    }

    int count = 0;
    size_t word_len = strlen(word);

    for (int i = 0; i < patternsSize; i++) {

        if (!patterns[i]) {
            continue;
        }

        size_t pattern_len = strlen(patterns[i]);

        if (pattern_len > word_len) {
            continue;
        }

        if (strstr(word, patterns[i]) != NULL) {
            count++;
        }
    }

    return count;
}