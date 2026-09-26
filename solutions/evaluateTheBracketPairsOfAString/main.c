#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 20011
#define MAX_CAPACITY 1000000

typedef struct Node {
    char* key;
    char* value;
    struct Node* next;
} Node;

/**
 * Calcula hash de uma chave usando DJB2.
 */
unsigned long hashKey(const char* s) {
    if (!s) return 0;

    unsigned long hash = 5381;

    while (*s) {
        hash = ((hash << 5) + hash) + (unsigned char)(*s);
        s++;
    }

    return hash % HASH_SIZE;
}

/**
 * Insere par chave-valor na tabela hash.
 * Duplica chave e valor para evitar vazamento de memória.
 */
int insert(Node** table, const char* key, const char* value) {
    if (!table || !key || !value) {
        return 0;  // Erro
    }

    unsigned long h = hashKey(key);

    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        return 0;  // Erro: malloc falhou
    }

    // Duplica chave
    node->key = (char*)malloc(strlen(key) + 1);
    if (!node->key) {
        free(node);
        return 0;
    }
    strcpy(node->key, key);

    // Duplica valor
    node->value = (char*)malloc(strlen(value) + 1);
    if (!node->value) {
        free(node->key);
        free(node);
        return 0;
    }
    strcpy(node->value, value);

    node->next = table[h];
    table[h] = node;

    return 1;  // Sucesso
}

/**
 * Encontra valor associado a uma chave.
 */
char* find(Node** table, const char* key) {
    if (!table || !key) {
        return NULL;
    }

    unsigned long h = hashKey(key);
    Node* cur = table[h];

    while (cur != NULL) {
        if (strcmp(cur->key, key) == 0) {
            return cur->value;
        }
        cur = cur->next;
    }

    return NULL;
}

/**
 * Libera toda a tabela hash.
 */
void freeTable(Node** table) {
    if (!table) return;

    for (int h = 0; h < HASH_SIZE; h++) {
        Node* cur = table[h];

        while (cur != NULL) {
            Node* next = cur->next;
            free(cur->key);
            free(cur->value);
            free(cur);
            cur = next;
        }
    }

    free(table);
}

/**
 * Avalia string com variáveis entre parênteses.
 * 
 * @param s String com variáveis entre parênteses
 * @param knowledge Array de pares [chave, valor]
 * @param knowledgeSize Tamanho do array
 * @param knowledgeColSize Tamanho de cada linha (não usado)
 * @return String processada, ou NULL se erro
 */
char* evaluate(
    char* s,
    char*** knowledge,
    int knowledgeSize,
    int* knowledgeColSize
) {
    // Validação de entrada
    if (!s || !knowledge || knowledgeSize < 0) {
        return NULL;
    }

    // Cria tabela hash
    Node** table = (Node**)calloc(HASH_SIZE, sizeof(Node*));
    if (!table) {
        return NULL;
    }

    // Insere conhecimento na tabela
    for (int i = 0; i < knowledgeSize; i++) {
        if (!knowledge[i] || !knowledge[i][0] || !knowledge[i][1]) {
            freeTable(table);
            return NULL;
        }

        if (!insert(table, knowledge[i][0], knowledge[i][1])) {
            freeTable(table);
            return NULL;
        }
    }

    int n = strlen(s);

    // Calcula capacidade com limite
    long long capacity = n + 1;
    for (int i = 0; i < knowledgeSize; i++) {
        capacity += strlen(knowledge[i][1]);
        if (capacity > MAX_CAPACITY) {
            freeTable(table);
            return NULL;
        }
    }

    // Aloca resultado
    char* ans = (char*)malloc((size_t)capacity * sizeof(char));
    if (!ans) {
        freeTable(table);
        return NULL;
    }

    int pos = 0;
    int i = 0;

    // Processa string
    while (i < n) {
        if (s[i] != '(') {
            ans[pos++] = s[i++];
            continue;
        }

        i++;  // Pula '('

        int start = i;

        // Encontra ')'
        while (i < n && s[i] != ')') {
            i++;
        }

        // Valida se encontrou ')'
        if (i >= n) {
            free(ans);
            freeTable(table);
            return NULL;
        }

        int len = i - start;

        // Valida variável vazia
        if (len == 0) {
            free(ans);
            freeTable(table);
            return NULL;
        }

        // Extrai chave
        char* key = (char*)malloc((len + 1) * sizeof(char));
        if (!key) {
            free(ans);
            freeTable(table);
            return NULL;
        }

        memcpy(key, s + start, len);
        key[len] = '\0';

        // Procura valor
        char* value = find(table, key);

        if (value != NULL) {
            int valueLen = strlen(value);

            // Verifica se cabe no buffer
            if (pos + valueLen > (int)capacity - 1) {
                free(key);
                free(ans);
                freeTable(table);
                return NULL;
            }

            memcpy(ans + pos, value, valueLen);
            pos += valueLen;
        } else {
            ans[pos++] = '?';
        }

        free(key);
        i++;  // Pula ')'
    }

    ans[pos] = '\0';

    freeTable(table);

    return ans;
}