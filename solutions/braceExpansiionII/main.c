#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_RESULT_SIZE 100000
#define MAX_WORD_LEN 64

typedef struct {
    char** words;
    int count;
} Set;

typedef struct {
    int success;
    const char* error;
} ParseResult;

static ParseResult lastError = {1, NULL};

/**
 * Duplica uma string com verificação de erro.
 */
static char* myStrdup(const char* str) {
    if (!str) return NULL;
    
    size_t len = strlen(str);
    char* r = malloc(len + 1);
    if (!r) {
        lastError.success = 0;
        lastError.error = "malloc falhou em myStrdup";
        return NULL;
    }
    strcpy(r, str);
    return r;
}

/**
 * Comparador para qsort.
 */
static int cmpstr(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

/**
 * Libera um Set.
 */
static void freeSet(Set s) {
    if (!s.words) return;
    for (int i = 0; i < s.count; i++) {
        if (s.words[i]) free(s.words[i]);
    }
    free(s.words);
}

/**
 * Remove duplicatas após ordenação.
 */
static Set dedupe(Set s) {
    if (s.count == 0) return s;

    qsort(s.words, s.count, sizeof(char*), cmpstr);

    int newCount = 1;
    for (int i = 1; i < s.count; i++) {
        if (strcmp(s.words[i], s.words[newCount - 1]) != 0) {
            s.words[newCount++] = s.words[i];
        } else {
            free(s.words[i]);
        }
    }
    s.count = newCount;
    return s;
}

/**
 * Cria um Set com uma única palavra.
 */
static Set makeSingleton(const char* word) {
    Set r = {NULL, 0};
    r.words = malloc(sizeof(char*));
    if (!r.words) {
        lastError.success = 0;
        lastError.error = "malloc falhou em makeSingleton";
        return r;
    }
    r.words[0] = myStrdup(word);
    if (!r.words[0]) {
        free(r.words);
        r.words = NULL;
        return r;
    }
    r.count = 1;
    return r;
}

/**
 * Concatenação cartesiana de dois Sets.
 */
static Set cartesianConcat(Set a, Set b) {
    Set r = {NULL, 0};

    // Verifica overflow
    if (a.count > MAX_RESULT_SIZE / b.count) {
        lastError.success = 0;
        lastError.error = "resultado muito grande (overflow)";
        freeSet(a);
        freeSet(b);
        return r;
    }

    r.count = a.count * b.count;
    r.words = malloc(sizeof(char*) * r.count);
    if (!r.words) {
        lastError.success = 0;
        lastError.error = "malloc falhou em cartesianConcat";
        freeSet(a);
        freeSet(b);
        return r;
    }

    int idx = 0;
    for (int i = 0; i < a.count; i++) {
        for (int j = 0; j < b.count; j++) {
            size_t len = strlen(a.words[i]) + strlen(b.words[j]);
            
            // Verifica tamanho
            if (len > 1000) {
                lastError.success = 0;
                lastError.error = "palavra muito longa";
                freeSet(a);
                freeSet(b);
                freeSet(r);
                return (Set){NULL, 0};
            }

            char* w = malloc(len + 1);
            if (!w) {
                lastError.success = 0;
                lastError.error = "malloc falhou em cartesianConcat (palavra)";
                freeSet(a);
                freeSet(b);
                freeSet(r);
                return (Set){NULL, 0};
            }

            strcpy(w, a.words[i]);
            strcat(w, b.words[j]);
            r.words[idx++] = w;
        }
    }

    freeSet(a);
    freeSet(b);
    return dedupe(r);
}

/**
 * União de dois Sets.
 */
static Set unionSets(Set a, Set b) {
    Set r = {NULL, 0};

    // Verifica overflow
    if (a.count > MAX_RESULT_SIZE - b.count) {
        lastError.success = 0;
        lastError.error = "resultado muito grande (overflow)";
        freeSet(a);
        freeSet(b);
        return r;
    }

    r.count = a.count + b.count;
    r.words = malloc(sizeof(char*) * r.count);
    if (!r.words) {
        lastError.success = 0;
        lastError.error = "malloc falhou em unionSets";
        freeSet(a);
        freeSet(b);
        return r;
    }

    int idx = 0;
    for (int i = 0; i < a.count; i++) {
        r.words[idx++] = a.words[i];
    }
    for (int i = 0; i < b.count; i++) {
        r.words[idx++] = b.words[i];
    }

    free(a.words);
    free(b.words);
    return dedupe(r);
}

// Forward declaration
static Set parseUnion(char** s);

/**
 * Parseia um fator: '{' union '}' ou palavra.
 */
static Set parseFactor(char** s) {
    if (!s || !*s) {
        lastError.success = 0;
        lastError.error = "ponteiro inválido em parseFactor";
        return (Set){NULL, 0};
    }

    if (**s == '{') {
        (*s)++;
        Set r = parseUnion(s);
        if (!lastError.success) return r;

        if (**s != '}') {
            lastError.success = 0;
            lastError.error = "'}' esperado";
            freeSet(r);
            return (Set){NULL, 0};
        }
        (*s)++;
        return r;
    } else {
        char buf[MAX_WORD_LEN];
        int i = 0;

        while (**s >= 'a' && **s <= 'z') {
            if (i >= MAX_WORD_LEN - 1) {
                lastError.success = 0;
                lastError.error = "palavra muito longa";
                return (Set){NULL, 0};
            }
            buf[i++] = **s;
            (*s)++;
        }

        if (i == 0) {
            lastError.success = 0;
            lastError.error = "palavra vazia";
            return (Set){NULL, 0};
        }

        buf[i] = '\0';
        return makeSingleton(buf);
    }
}

/**
 * Parseia concatenação: factor factor*
 */
static Set parseConcat(char** s) {
    if (!s || !*s) {
        lastError.success = 0;
        lastError.error = "ponteiro inválido em parseConcat";
        return (Set){NULL, 0};
    }

    Set r = parseFactor(s);
    if (!lastError.success) return r;

    while (**s && **s != ',' && **s != '}') {
        Set next = parseFactor(s);
        if (!lastError.success) {
            freeSet(r);
            return next;
        }
        r = cartesianConcat(r, next);
        if (!lastError.success) return r;
    }

    return r;
}

/**
 * Parseia união: concat (',' concat)*
 */
static Set parseUnion(char** s) {
    if (!s || !*s) {
        lastError.success = 0;
        lastError.error = "ponteiro inválido em parseUnion";
        return (Set){NULL, 0};
    }

    Set r = parseConcat(s);
    if (!lastError.success) return r;

    while (**s == ',') {
        (*s)++;
        Set next = parseConcat(s);
        if (!lastError.success) {
            freeSet(r);
            return next;
        }
        r = unionSets(r, next);
        if (!lastError.success) return r;
    }

    return r;
}

/**
 * Expande expressão com chaves.
 * 
 * @param expression Expressão com chaves
 * @param returnSize Ponteiro para retornar tamanho
 * @return Array de strings expandidas, ou NULL se erro
 */
char** braceExpansionII(char* expression, int* returnSize) {
    // Validação de entrada
    if (!expression || !returnSize) {
        if (returnSize) *returnSize = 0;
        return NULL;
    }

    // Reseta estado de erro
    lastError.success = 1;
    lastError.error = NULL;

    char* s = expression;
    Set result = parseConcat(&s);

    // Verifica se houve erro durante parsing
    if (!lastError.success) {
        freeSet(result);
        *returnSize = 0;
        return NULL;
    }

    // Verifica se há caracteres não processados
    if (*s != '\0') {
        lastError.success = 0;
        lastError.error = "caracteres não esperados no final";
        freeSet(result);
        *returnSize = 0;
        return NULL;
    }

    result = dedupe(result);

    *returnSize = result.count;
    return result.words;
}