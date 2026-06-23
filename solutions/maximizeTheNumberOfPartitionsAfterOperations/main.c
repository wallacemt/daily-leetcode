#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ALPHABET_SIZE 26

typedef struct {
    int *next_pos;
    int n;
} NextPosTable;

typedef struct {
    int *partition_start;
    int *pref;
    int *suff;
    int n;
} PartitionInfo;

static NextPosTable* build_next_pos_table(const char* s, int n) {
    NextPosTable *table = (NextPosTable*)malloc(sizeof(NextPosTable));
    if (!table) return NULL;
    
    table->n = n;
    table->next_pos = (int*)malloc((n + 1) * ALPHABET_SIZE * sizeof(int));
    if (!table->next_pos) {
        free(table);
        return NULL;
    }
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        table->next_pos[n * ALPHABET_SIZE + c] = n;
    }
    
    for (int i = n - 1; i >= 0; i--) {
        memcpy(&table->next_pos[i * ALPHABET_SIZE], 
               &table->next_pos[(i + 1) * ALPHABET_SIZE], 
               ALPHABET_SIZE * sizeof(int));
        table->next_pos[i * ALPHABET_SIZE + (s[i] - 'a')] = i;
    }
    
    return table;
}

static int compute_partition_end(const NextPosTable *table, int k, int start, 
                                  int i_pos, int orig_idx, int new_idx) {
    int positions[ALPHABET_SIZE];
    int count = 0;
    
    for (int c = 0; c < ALPHABET_SIZE; c++) {
        int first = table->next_pos[start * ALPHABET_SIZE + c];
        
        if (c == new_idx && i_pos >= start) {
            int np_at_start = table->next_pos[start * ALPHABET_SIZE + c];
            first = (i_pos < np_at_start) ? i_pos : np_at_start;
        } else if (c == orig_idx && i_pos >= start) {
            int np_at_start = table->next_pos[start * ALPHABET_SIZE + c];
            if (np_at_start == i_pos) {
                first = table->next_pos[(i_pos + 1) * ALPHABET_SIZE + c];
            }
        }
        
        if (first < table->n) {
            positions[count++] = first;
        }
    }
    
    if (count <= k) return table->n - 1;
    
    for (int i = 1; i < count; i++) {
        int key = positions[i];
        int j = i - 1;
        while (j >= 0 && positions[j] > key) {
            positions[j + 1] = positions[j];
            j--;
        }
        positions[j + 1] = key;
    }
    
    return positions[k] - 1;
}

static void compute_prefix_partitions(const char* s, int n, int k, 
                                       int *partition_start, int *pref) {
    int start = 0, parts = 0;
    int cnt[ALPHABET_SIZE];
    
    while (start < n) {
        memset(cnt, 0, sizeof(cnt));
        int distinct = 0, j = start;
        
        while (j < n) {
            int idx = s[j] - 'a';
            if (cnt[idx] == 0) {
                if (distinct == k) break;
                distinct++;
            }
            cnt[idx]++;
            j++;
        }
        
        parts++;
        for (int t = start; t < j; t++) {
            partition_start[t] = start;
            pref[t] = parts;
        }
        start = j;
    }
}

static void compute_suffix_partitions(const char* s, int n, int k, int *suff) {
    int end = n - 1, parts = 0;
    int cnt[ALPHABET_SIZE];
    
    while (end >= 0) {
        memset(cnt, 0, sizeof(cnt));
        int distinct = 0, j = end;
        
        while (j >= 0) {
            int idx = s[j] - 'a';
            if (cnt[idx] == 0) {
                if (distinct == k) break;
                distinct++;
            }
            cnt[idx]++;
            j--;
        }
        
        parts++;
        for (int t = j + 1; t <= end; t++) {
            suff[t] = parts;
        }
        end = j;
    }
}

static int try_improvement(const NextPosTable *table, const PartitionInfo *info, 
                           int k, int i, const char* s) {
    int L = info->partition_start[i];
    int orig = s[i] - 'a';
    int leftParts = (L > 0) ? info->pref[L - 1] : 0;
    int max_improvement = 0;
    
    for (int new_idx = 0; new_idx < ALPHABET_SIZE; new_idx++) {
        if (new_idx == orig) continue;
        
        int r = compute_partition_end(table, k, L, i, orig, new_idx);
        int cand;
        
        if (r >= i) {
            int rightParts = (r + 1 < info->n) ? info->suff[r + 1] : 0;
            cand = 1 + leftParts + rightParts;
        } else {
            int r2 = compute_partition_end(table, k, r + 1, i, orig, new_idx);
            int rightParts = (r2 + 1 < info->n) ? info->suff[r2 + 1] : 0;
            cand = 2 + leftParts + rightParts;
        }
        
        if (cand > max_improvement) {
            max_improvement = cand;
        }
    }
    
    return max_improvement;
}

int maxPartitionsAfterOperations(char* s, int k) {
    int n = (int)strlen(s);
    if (n == 0) return 0;
    if (k <= 0) return n;
    
    NextPosTable *table = build_next_pos_table(s, n);
    if (!table) return 0;
    
    PartitionInfo info;
    info.n = n;
    info.partition_start = (int*)malloc(n * sizeof(int));
    info.pref = (int*)malloc(n * sizeof(int));
    info.suff = (int*)malloc(n * sizeof(int));
    
    if (!info.partition_start || !info.pref || !info.suff) {
        free(table->next_pos);
        free(table);
        free(info.partition_start);
        free(info.pref);
        free(info.suff);
        return 0;
    }
    
    compute_prefix_partitions(s, n, k, info.partition_start, info.pref);
    compute_suffix_partitions(s, n, k, info.suff);
    
    int ans = info.suff[0];
    
    for (int i = 0; i < n; i++) {
        int cand = try_improvement(table, &info, k, i, s);
        if (cand > ans) ans = cand;
    }
    
    free(table->next_pos);
    free(table);
    free(info.partition_start);
    free(info.pref);
    free(info.suff);
    
    return ans;
}