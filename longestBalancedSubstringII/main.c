#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HASH_SIZE 1000003 

typedef struct {
    long long key;
    int val;
    int used;
} HashEntry;

static inline int get_idx(HashEntry* table, long long key) {
    unsigned long long h = (unsigned long long)key;
    h ^= (h >> 17);
    h ^= (h >> 11);
    
    unsigned int idx = h % HASH_SIZE;
    
    while (table[idx].used) {
        if (table[idx].key == key) {
            return idx;
        }
        idx++;
        if (idx == HASH_SIZE) {
            idx = 0; 
        }
    }
    return idx;
}

static inline void insert_map(HashEntry* table, long long key, int val) {
    int h = get_idx(table, key);
    if (!table[h].used) {
        table[h].key = key;
        table[h].val = val;
        table[h].used = 1;
    }
}

static inline int query_map(HashEntry* table, long long key) {
    int h = get_idx(table, key);
    if (table[h].used) {
        return table[h].val;
    }
    return -2;
}

int solvePair(char* s, int n, char c1, char c2, char forbidden, int* pos, int* modified) {
    int max_len = 0;
    
    for (int k = 0; k <= 2 * n; k++) {
        pos[k] = -2;
    }
    
    int mod_count = 0;
    int offset = n;
    int diff = 0;

    pos[0 + offset] = -1;
    modified[mod_count++] = 0 + offset;

    for (int i = 0; i < n; i++) {
        if (s[i] == forbidden) {
            diff = 0;
            while (mod_count > 0) {
                pos[modified[--mod_count]] = -2;
            }
            
            pos[0 + offset] = i;
            modified[mod_count++] = 0 + offset;
        } else {
            if (s[i] == c1) {
                diff++;
            } else if (s[i] == c2) {
                diff--;
            }
            
            int idx = diff + offset;
            
            if (pos[idx] != -2) {
                int curr_len = i - pos[idx];
                if (curr_len > max_len) max_len = curr_len;
            } else {
                pos[idx] = i;
                modified[mod_count++] = idx;
            }
        }
    }
    return max_len;
}

int longestBalanced(char* s) {
    int n = strlen(s);
    int ans = 0;

    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (i > 0 && s[i] == s[i - 1]) cnt++;
        else cnt = 1;
        if (cnt > ans) {
            ans = cnt;
        }
    }

    int* pos = (int*)malloc(sizeof(int) * (2 * n + 1));
    int* modified = (int*)malloc(sizeof(int) * (n + 1));

    int res;
    res = solvePair(s, n, 'a', 'b', 'c', pos, modified); 
    if (res > ans) {
        ans = res;
    }
    
    res = solvePair(s, n, 'a', 'c', 'b', pos, modified); 
    if (res > ans) {
        ans = res;
    }
    
    res = solvePair(s, n, 'b', 'c', 'a', pos, modified); 
    if (res > ans) {
        ans = res;
    }

    free(pos);
    free(modified);

    HashEntry* map = (HashEntry*)calloc(HASH_SIZE, sizeof(HashEntry));
    if (!map) {
        return ans; 
    }
    
    insert_map(map, 0, -1);
    
    int a = 0, b = 0, c = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'a') {
            a++;
        } else if (s[i] == 'b') {
            b++;
        } else {
            c++;
        }

        long long key = ((unsigned long long)(unsigned int)(a - b) << 32) | (unsigned int)(b - c);
        
        int prev_idx = query_map(map, key);
        if (prev_idx != -2) {
            int curr = i - prev_idx;
            if (curr > ans) {
                ans = curr;
            }
        } else {
            insert_map(map, key, i);
        }
    }
    free(map);

    return ans;
}