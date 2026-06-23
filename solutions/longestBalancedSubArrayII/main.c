#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int min_val;
    int max_val;
    int lazy;
} Node;

Node* tree;
int tree_size;

// Inline para evitar overhead de função
static inline void push(int node) {
    int lazy = tree[node].lazy;
    if (lazy) {
        int l = 2 * node;
        int r = l + 1;
        
        tree[l].lazy += lazy;
        tree[l].min_val += lazy;
        tree[l].max_val += lazy;

        tree[r].lazy += lazy;
        tree[r].min_val += lazy;
        tree[r].max_val += lazy;

        tree[node].lazy = 0;
    }
}

static inline int min_int(int a, int b) {
    return a < b ? a : b;
}

static inline int max_int(int a, int b) {
    return a > b ? a : b;
}

void update(int node, int st, int en, int l, int r, int val) {
    if (l > en || r < st) {
        return;
    }
    if (l <= st && en <= r) {
        tree[node].lazy += val;
        tree[node].min_val += val;
        tree[node].max_val += val;
        return;
    }
    push(node);
    int m = (st + en) >> 1;  // Shift é mais rápido que divisão
    int left_child = 2 * node;
    int right_child = left_child + 1;
    
    update(left_child, st, m, l, r, val);
    update(right_child, m + 1, en, l, r, val);
    
    tree[node].min_val = min_int(tree[left_child].min_val, tree[right_child].min_val);
    tree[node].max_val = max_int(tree[left_child].max_val, tree[right_child].max_val);
}

int findFirstZero(int node, int st, int en, int lim) {
    if (tree[node].min_val > 0 || tree[node].max_val < 0) {
        return -1;
    }
    if (st > lim) {
        return -1;
    }

    if (st == en) {
        return (tree[node].min_val == 0) ? st : -1;
    }

    push(node);
    int m = (st + en) >> 1;
    int left_child = 2 * node;
    int right_child = left_child + 1;

    int res = findFirstZero(left_child, st, m, lim);
    if (res != -1) {
        return res;
    }

    return findFirstZero(right_child, m + 1, en, lim);
}

int longestBalanced(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }
    
    tree_size = 4 * numsSize;
    tree = (Node*)malloc(tree_size * sizeof(Node));
    memset(tree, 0, tree_size * sizeof(Node));
    
    // Mantém alocação original de 100005 para evitar overflow
    int* pos = (int*)malloc(100005 * sizeof(int));
    memset(pos, -1, 100005 * sizeof(int));
    
    int max_len = 0;

    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        
        // Validação de segurança
        if (val < 0 || val >= 100005) {
            continue;
        }
        
        int pre = pos[val];
        int ch = (val & 1) ? -1 : 1;  // Bitwise é mais rápido que modulo

        update(1, 0, numsSize - 1, pre + 1, i, ch);
        pos[val] = i;

        int l = findFirstZero(1, 0, numsSize - 1, i);
        if (l != -1) {
            max_len = max_int(max_len, i - l + 1);
        }
    }

    free(tree);
    free(pos);
    return max_len;
}