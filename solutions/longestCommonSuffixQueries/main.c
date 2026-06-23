#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct TrieNode {
    struct TrieNode* children[26];
    int best;
    int len;  // Mantém para comparação correta
} TrieNode;

TrieNode* createNode() {
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    node->best = -1;
    node->len = INT_MAX;
    for (int i = 0; i < 26; i++) 
        node->children[i] = NULL;
    return node;
}

void insert(TrieNode* root, int idx, const char* word, int len) {
    TrieNode* curr = root;
    
    for (int i = len - 1; i >= 0; i--) {
        int c = word[i] - 'a';
        if (!curr->children[c]) 
            curr->children[c] = createNode();
        curr = curr->children[c];
        
        // Atualiza se: primeiro elemento OU comprimento menor
        // OU mesmo comprimento mas índice menor (lexicograficamente)
        if (curr->best == -1 || len < curr->len || 
            (len == curr->len && idx < curr->best)) {
            curr->best = idx;
            curr->len = len;
        }
    }
}

int search(TrieNode* root, const char* word, int len) {
    TrieNode* curr = root;
    
    for (int i = len - 1; i >= 0; i--) {
        int c = word[i] - 'a';
        if (!curr->children[c]) 
            break;
        curr = curr->children[c];
    }
    
    return curr->best;
}

void freeTrie(TrieNode* root) {
    if (!root) return;
    
    for (int i = 0; i < 26; i++) {
        if (root->children[i]) 
            freeTrie(root->children[i]);
    }
    free(root);
}

int* stringIndices(char** wordsContainer, int wordsContainerSize, 
                   char** wordsQuery, int wordsQuerySize, int* returnSize) {
    if (!wordsContainer || !wordsQuery || wordsContainerSize == 0) {
        *returnSize = 0;
        return NULL;
    }

    TrieNode* root = createNode();
    int minLenIdx = 0;
    int minLen = strlen(wordsContainer[0]);

    // Pré-calcula comprimentos
    int* lengths = (int*)malloc(sizeof(int) * wordsContainerSize);
    
    for (int i = 0; i < wordsContainerSize; i++) {
        lengths[i] = strlen(wordsContainer[i]);
        insert(root, i, wordsContainer[i], lengths[i]);
        
        if (lengths[i] < minLen) {
            minLen = lengths[i];
            minLenIdx = i;
        }
    }

    *returnSize = wordsQuerySize;
    int* result = (int*)malloc(sizeof(int) * wordsQuerySize);

    for (int i = 0; i < wordsQuerySize; i++) {
        int len = strlen(wordsQuery[i]);
        int idx = search(root, wordsQuery[i], len);
        result[i] = (idx == -1) ? minLenIdx : idx;
    }

    free(lengths);
    freeTrie(root);
    return result;
}