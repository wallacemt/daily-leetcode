#include <string.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char* str;
    int len;
} Block;

int cmp_optimized(const void* a, const void* b) {
    const Block* ba = (const Block*)a;
    const Block* bb = (const Block*)b;
    
    int minlen = ba->len < bb->len ? ba->len : bb->len;
    int cmp = strncmp(bb->str, ba->str, minlen);
    
    if (cmp != 0) return cmp;
    return bb->len - ba->len; 
}

char* makeLargestSpecial(char* s) {
    int n = strlen(s);
    
    Block* blocks = malloc(sizeof(Block) * (n / 2 + 1));
    int block_count = 0;
    
    char* ans = malloc(n + 1);
    int ans_pos = 0;
    
    int cnt = 0, idx = 0;

    for (int i = 0; i < n; i++) {
        cnt += (s[i] == '1') ? 1 : -1;

        if (cnt == 0) {
            int len = i - idx - 1;
            
            char* sub = malloc(len + 1);
            strncpy(sub, s + idx + 1, len);
            sub[len] = '\0';

            // Recursão
            char* inner = makeLargestSpecial(sub);
            free(sub);

            int block_len = strlen(inner) + 2;
            char* block = malloc(block_len + 1);
            block[0] = '1';
            strcpy(block + 1, inner);
            block[block_len - 1] = '0';
            block[block_len] = '\0';
            
            free(inner);

            blocks[block_count].str = block;
            blocks[block_count].len = block_len;
            block_count++;
            
            idx = i + 1;
        }
    }

    qsort(blocks, block_count, sizeof(Block), cmp_optimized);
    for (int i = 0; i < block_count; i++) {
        strcpy(ans + ans_pos, blocks[i].str);
        ans_pos += blocks[i].len;
        free(blocks[i].str);
    }
    ans[ans_pos] = '\0';

    free(blocks);
    return ans;
}