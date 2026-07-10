typedef struct {
    int value;
    int index;
} Pair;

int cmpPair(const void* a, const void* b) {
    Pair* p1 = (Pair*)a;
    Pair* p2 = (Pair*)b;

    if (p1->value != p2->value) {
        return p1->value - p2->value;
    }
    return p1->index - p2->index;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* pathExistenceQueries( int n, int* nums, int numsSize, int maxDiff, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    int LOG = 18;

    Pair* vec = (Pair*)malloc(sizeof(Pair) * n);
    for (int i = 0; i < n; i++) {
        vec[i].value = nums[i];
        vec[i].index = i;
    }

    qsort(vec, n, sizeof(Pair), cmpPair);

    int* getSortIdx = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        getSortIdx[vec[i].index] = i;
    }

    int** st = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; i++) {
        st[i] = (int*)calloc(LOG, sizeof(int));
    }

    int l = 0;

    for (int r = 0; r < n; r++) {
        while (vec[r].value - vec[l].value > maxDiff) {
            st[l][0] = r - 1;
            l++;
        }
    }

    while (l < n) {
        st[l][0] = n - 1;
        l++;
    }

    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < n; i++) {
            st[i][j] = st[st[i][j - 1]][j - 1];
        }
    }

    int* ans = (int*)malloc(sizeof(int) * queriesSize);
    for (int i = 0; i < queriesSize; i++) {
        ans[i] = -1;

        int a = getSortIdx[queries[i][0]];
        int b = getSortIdx[queries[i][1]];

        if (a > b) {
            int temp = a;
            a = b;
            b = temp;
        }

        if (a == b) {
            ans[i] = 0;
            continue;
        }

        int cur = a;
        int step = 0;

        for (int j = LOG - 1; j >= 0; j--) {
            if (st[cur][j] < b) {
                step += 1 << j;
                cur = st[cur][j];
            }
        }

        if (st[cur][0] >= b) {
            ans[i] = step + 1;
        }
    }

    for (int i = 0; i < n; i++) {
        free(st[i]);
    }
    free(st);
    free(vec);
    free(getSortIdx);

    *returnSize = queriesSize;
    return ans;
}
