#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN 305
#define MAX_RESULT 610

// Estrutura para encapsular estado (evita globais)
typedef struct {
    int half_cnt[26];
    char mid_char;
    int n_half;
    const char* target_str;
    char* half_str;
    size_t max_len;
} PalindromeState;

// Reverter string in-place (mais eficiente)
static inline void reverse_string(char* str, int len) {
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

// Construir resultado uma única vez
static char* build_result(const PalindromeState* state) {
    int total_len = state->n_half * 2 + (state->mid_char ? 1 : 0);
    
    char* result = (char*)malloc(total_len + 1);
    if (!result) return NULL;

    // Copiar primeira metade
    memcpy(result, state->half_str, state->n_half);
    
    // Adicionar caractere do meio
    int pos = state->n_half;
    if (state->mid_char) {
        result[pos++] = state->mid_char;
    }
    
    // Copiar segunda metade (reversa)
    for (int i = 0; i < state->n_half; i++) {
        result[pos++] = state->half_str[state->n_half - i - 1];
    }
    
    result[pos] = '\0';
    return result;
}

// Comparar palindromo com target (evita construir string)
static bool compare_palindrome(const PalindromeState* state) {
    int target_len = strlen(state->target_str);
    int palindrome_len = state->n_half * 2 + (state->mid_char ? 1 : 0);
    
    // Rápida falha: tamanhos diferentes
    if (palindrome_len != target_len)
        return palindrome_len > target_len;

    // Comparar primeira metade
    int cmp = memcmp(state->half_str, state->target_str, state->n_half);
    if (cmp != 0)
        return cmp > 0;

    // Comparar meio
    int mid_pos = state->n_half;
    if (state->mid_char) {
        if (state->mid_char != state->target_str[mid_pos])
            return state->mid_char > state->target_str[mid_pos];
        mid_pos++;
    }

    // Comparar segunda metade (reversa)
    for (int i = 0; i < state->n_half; i++) {
        char c = state->half_str[state->n_half - i - 1];
        if (c != state->target_str[mid_pos + i])
            return c > state->target_str[mid_pos + i];
    }

    return false; // Igual, não é maior
}

static bool find_palindrome(PalindromeState* state, int k, bool is_greater) {
    if (k == state->n_half) {
        return compare_palindrome(state);
    }

    char start_c = is_greater ? 'a' : state->target_str[k];
    for (char c = start_c; c <= 'z'; ++c) {
        if (state->half_cnt[c - 'a'] > 0) {
            state->half_str[k] = c;
            state->half_cnt[c - 'a']--;

            bool found = find_palindrome(state, k + 1, 
                                        is_greater || (c > state->target_str[k]));
            if (found)
                return true;

            state->half_cnt[c - 'a']++;
        }
    }
    return false;
}

char* lexPalindromicPermutation(const char* s, const char* target) {
    // Validação de entrada
    if (!s || !target || strlen(s) > MAX_LEN || strlen(target) > MAX_LEN) {
        return strdup("");
    }

    int n = strlen(s);
    int cnt[26] = {0};

    // Contar caracteres
    for (int i = 0; i < n; i++) {
        if (s[i] < 'a' || s[i] > 'z')
            return strdup(""); // Entrada inválida
        cnt[s[i] - 'a']++;
    }

    // Verificar caracteres ímpares
    int odd = 0;
    char mid_char = '\0';
    for (int i = 0; i < 26; i++) {
        if (cnt[i] % 2 != 0) {
            odd++;
            mid_char = 'a' + i;
        }
    }

    if (odd > 1)
        return strdup("");

    // Inicializar estado
    PalindromeState state = {
        .mid_char = mid_char,
        .n_half = n / 2,
        .target_str = target,
        .max_len = MAX_LEN
    };

    // Alocar half_str dinamicamente
    state.half_str = (char*)malloc(state.n_half + 1);
    if (!state.half_str)
        return strdup("");

    state.half_str[state.n_half] = '\0';

    // Copiar contagens
    for (int i = 0; i < 26; i++)
        state.half_cnt[i] = cnt[i] / 2;

    // Buscar palindromo
    char* result = NULL;
    if (find_palindrome(&state, 0, false)) {
        result = build_result(&state);
    }

    free(state.half_str);
    return result ? result : strdup("");
}
 