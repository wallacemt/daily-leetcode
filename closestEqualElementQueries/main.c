#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int key;
    int val;
} HashEntry;

// Hash function com tamanho dinâmico
int hash_func(int key, int size) {
    unsigned int h = (unsigned int)(key ^ (key >> 16));
    return h % size;
}

void hash_put(HashEntry* table, int key, int val, int size) {
    int idx = hash_func(key, size);
    while (table[idx].key != INT_MIN && table[idx].key != key) {
        idx = (idx + 1) % size;
    }
    table[idx].key = key;
    table[idx].val = val;
}

int hash_get(HashEntry* table, int key, int size) {
    int idx = hash_func(key, size);
    while (table[idx].key != INT_MIN) {
        if (table[idx].key == key) {
            return table[idx].val;
        }
        idx = (idx + 1) % size;
    }
    return -1;
}

int* solveQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    int n = numsSize;
    
    int* minDist = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        minDist[i] = n;  
    }
    
    // OTIMIZAÇÃO 1: Hash table com tamanho dinâmico
    int hash_size = (n < 100) ? 256 : (n < 1000) ? 1024 : 200003;
    HashEntry* lastSeen = (HashEntry*)malloc(hash_size * sizeof(HashEntry));
    for (int i = 0; i < hash_size; ++i) {
        lastSeen[i].key = INT_MIN;
        lastSeen[i].val = -1;
    }

    for (int i = 0; i < n * 2; ++i) {
        int index = i % n;
        int num = nums[index];
        
        int prevIndex_raw = hash_get(lastSeen, num, hash_size);
        
        if (prevIndex_raw != -1) {
            int prevIndex = prevIndex_raw % n;
            int d = i - prevIndex_raw;
            
            minDist[index] = MIN(minDist[index], d);
            minDist[prevIndex] = MIN(minDist[prevIndex], d);
        }
        
        hash_put(lastSeen, num, i, hash_size);
    }

    *returnSize = queriesSize;
    int* ans = (int*)malloc(queriesSize * sizeof(int));
    
    for (int i = 0; i < queriesSize; ++i) {
        int query = queries[i];
        ans[i] = (minDist[query] == n) ? -1 : minDist[query];
    }

    free(lastSeen);
    free(minDist);

    return ans;
}