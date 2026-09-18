#include <stdlib.h>
#include <string.h>

#define CHAR_SET_SZ 26

typedef struct {
    int start;
    int end;
} Range;

// Compare intervals: sort by end ascending, then start descending
int compareRanges(const void* a, const void* b) {
    Range* r1 = (Range*)a;
    Range* r2 = (Range*)b;
    if (r1->end == r2->end) {
        return r2->start - r1->start;
    }
    return r1->end - r2->end;
}

char** maxNumOfSubstrings(char* s, int* returnSize) {
    // Validação de entrada
    if (!s || !returnSize) {
        if (returnSize) {
            *returnSize = 0;
        }
        return NULL;
    }

    int n = strlen(s);
    if (n == 0) {
        char** res = (char**)malloc(sizeof(char*));
        if (res) {
            *returnSize = 0;
        }
        return res;
    }

    int firstIdx[CHAR_SET_SZ];
    int lastIdx[CHAR_SET_SZ];

    // Inicializa arrays
    for (int i = 0; i < CHAR_SET_SZ; i++) {
        firstIdx[i] = n;
        lastIdx[i] = -1;
    }

    // 1. Calcula primeira e última ocorrência de cada caractere
    for (int i = 0; i < n; i++) {
        int c = s[i] - 'a';
        if (firstIdx[c] == n) {
            firstIdx[c] = i;
        }
        lastIdx[c] = i;
    }

    // 2. Identifica ranges válidos
    Range* validRanges = (Range*)malloc(CHAR_SET_SZ * sizeof(Range));
    if (!validRanges) {
        *returnSize = 0;
        char** res = (char**)malloc(sizeof(char*));
        return res;
    }

    int validCount = 0;

    for (int i = 0; i < CHAR_SET_SZ; i++) {
        if (firstIdx[i] == n) continue;

        int start = firstIdx[i];
        int end = lastIdx[i];
        int isValid = 1;

        // Valida e expande o range
        for (int j = start; j <= end; j++) {
            int c = s[j] - 'a';
            // Se caractere interno começa antes, range é inválido
            if (firstIdx[c] < start) {
                isValid = 0;
                break;
            }
            // Expande end se necessário
            if (lastIdx[c] > end) {
                end = lastIdx[c];
            }
        }

        if (isValid) {
            validRanges[validCount].start = start;
            validRanges[validCount].end = end;
            validCount++;
        }
    }

    // 3. Ordena ranges
    qsort(validRanges, validCount, sizeof(Range), compareRanges);

    // 4. Aloca resultado com verificação
    char** res = (char**)malloc((validCount + 1) * sizeof(char*));
    if (!res) {
        free(validRanges);
        *returnSize = 0;
        return NULL;
    }

    *returnSize = 0;
    int lastIncludedEnd = -1;

    // 5. Seleciona greedily ranges não-sobrepostos
    for (int i = 0; i < validCount; i++) {
        int start = validRanges[i].start;
        int end = validRanges[i].end;

        if (start > lastIncludedEnd) {
            int len = end - start + 1;
            char* substring = (char*)malloc((len + 1) * sizeof(char));

            if (!substring) {
                // Libera memória alocada até agora
                for (int j = 0; j < *returnSize; j++) {
                    free(res[j]);
                }
                free(res);
                free(validRanges);
                *returnSize = 0;
                return NULL;
            }
 
            memcpy(substring, s + start, len);
            substring[len] = '\0';

            res[*returnSize] = substring;
            (*returnSize)++;
            lastIncludedEnd = end;
        }
    }

    free(validRanges);
    return res;
}