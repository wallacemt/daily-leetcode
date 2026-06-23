#define MEMO_CAP 131071  

typedef struct {
    uint64_t key;
    unsigned char used;
    unsigned char val;
} MemoEntry;

static uint32_t gMapMask[26 * 26];

static uint64_t pack_key(const char *s) {
    int len = (int)strlen(s);
    uint64_t key = (uint64_t)len;
    for (int i = 0; i < len; i++) {
        key = key * 27ULL + (uint64_t)(s[i] - 'A' + 1);
    }
    return key;
}

static unsigned char memo_get(MemoEntry *memo, uint64_t key, unsigned char *outVal) {
    uint32_t idx = (uint32_t)(key % MEMO_CAP);
    while (memo[idx].used) {
        if (memo[idx].key == key) {
            *outVal = memo[idx].val;
            return 1;
        }
        idx++;
        if (idx == MEMO_CAP) idx = 0;
    }
    return 0;
}

static void memo_put(MemoEntry *memo, uint64_t key, unsigned char val) {
    uint32_t idx = (uint32_t)(key % MEMO_CAP);
    while (memo[idx].used) {
        if (memo[idx].key == key) {
            memo[idx].val = val;
            return;
        }
        idx++;
        if (idx == MEMO_CAP) idx = 0;
    }
    memo[idx].used = 1;
    memo[idx].key = key;
    memo[idx].val = val;
}

static bool dfs_row(const char *row, MemoEntry *memo);

static bool build_next(const char *row, int n, int i, char *nextRow, MemoEntry *memo) {
    if (i == n - 1) {
        nextRow[n - 1] = '\0';
        return dfs_row(nextRow, memo);
    }

    int a = row[i] - 'A';
    int b = row[i + 1] - 'A';
    uint32_t mask = gMapMask[a * 26 + b];
    if (mask == 0) return false;

    while (mask) {
        uint32_t bit = mask & (~mask + 1u);
        int c = __builtin_ctz(mask);
        nextRow[i] = (char)('A' + c);
        if (build_next(row, n, i + 1, nextRow, memo)) return true;
        mask ^= bit;
    }

    return false;
}

static bool dfs_row(const char *row, MemoEntry *memo) {
    if (row[1] == '\0') return true;

    uint64_t key = pack_key(row);
    unsigned char cached;
    if (memo_get(memo, key, &cached)) return cached != 0;

    int n = (int)strlen(row);
    for (int i = 0; i < n - 1; i++) {
        int a = row[i] - 'A';
        int b = row[i + 1] - 'A';
        if (gMapMask[a * 26 + b] == 0) {
            memo_put(memo, key, 0);
            return false;
        }
    }

    char *nextRow = (char *)malloc((size_t)n);
    bool ok = build_next(row, n, 0, nextRow, memo);
    free(nextRow);

    memo_put(memo, key, ok ? 1 : 0);
    return ok;
}

bool pyramidTransition(char* bottom, char** allowed, int allowedSize) {
    memset(gMapMask, 0, sizeof(gMapMask));

    for (int i = 0; i < allowedSize; i++) {
        char *t = allowed[i];
        int a = t[0] - 'A';
        int b = t[1] - 'A';
        int c = t[2] - 'A';
        gMapMask[a * 26 + b] |= (1u << c);
    }

    MemoEntry *memo = (MemoEntry *)calloc(MEMO_CAP, sizeof(MemoEntry));
    bool ans = dfs_row(bottom, memo);
    free(memo);
    return ans;
}