/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdlib.h>
#include <string.h>

typedef struct {
    char leftChar;
    char rightChar;
    int length;
    int prefix;
    int suffix;
    int best;
} Node;

// Inline para evitar overhead de function call
static inline Node mergeNodes(const Node* left, const Node* right) {
    Node res;
    
    res.leftChar = left->leftChar;
    res.rightChar = right->rightChar;
    res.length = left->length + right->length;
    res.prefix = left->prefix;
    res.suffix = right->suffix;
    res.best = (left->best > right->best) ? left->best : right->best;

    // Otimização: verificar condição uma única vez
    if (left->rightChar == right->leftChar) {
        if (left->prefix == left->length) {
            res.prefix = left->length + right->prefix;
        }
        
        if (right->suffix == right->length) {
            res.suffix = right->length + left->suffix;
        }
        
        int combined = left->suffix + right->prefix;
        if (combined > res.best) {
            res.best = combined;
        }
    }

    return res;
}

void build(
    Node* tree,
    const char* s,
    int node,
    int start,
    int end
) {
    if (start == end) {
        char ch = s[start];
        tree[node] = (Node){
            .leftChar = ch,
            .rightChar = ch,
            .length = 1,
            .prefix = 1,
            .suffix = 1,
            .best = 1
        };
        return;
    }

    int mid = start + ((end - start) >> 1);  // Bit shift é mais rápido

    build(tree, s, node * 2, start, mid);
    build(tree, s, node * 2 + 1, mid + 1, end);

    tree[node] = mergeNodes(
        &tree[node * 2],
        &tree[node * 2 + 1]
    );
}

void update(
    Node* tree,
    int node,
    int start,
    int end,
    int index,
    char ch
) {
    if (start == end) {
        tree[node] = (Node){
            .leftChar = ch,
            .rightChar = ch,
            .length = 1,
            .prefix = 1,
            .suffix = 1,
            .best = 1
        };
        return;
    }

    int mid = start + ((end - start) >> 1);

    if (index <= mid) {
        update(tree, node * 2, start, mid, index, ch);
    } else {
        update(tree, node * 2 + 1, mid + 1, end, index, ch);
    }

    tree[node] = mergeNodes(
        &tree[node * 2],
        &tree[node * 2 + 1]
    );
}

int* longestRepeating(
    char* s,
    char* queryCharacters,
    int* queryIndices,
    int queryIndicesSize,
    int* returnSize
) {
    int n = strlen(s);
    
    // Alocação única e mais eficiente
    Node* tree = (Node*)malloc(4 * n * sizeof(Node));
    int* answer = (int*)malloc(queryIndicesSize * sizeof(int));

    build(tree, s, 1, 0, n - 1);

    for (int i = 0; i < queryIndicesSize; i++) {
        update(tree, 1, 0, n - 1, queryIndices[i], queryCharacters[i]);
        answer[i] = tree[1].best;
    }

    free(tree);
    *returnSize = queryIndicesSize;

    return answer;
}