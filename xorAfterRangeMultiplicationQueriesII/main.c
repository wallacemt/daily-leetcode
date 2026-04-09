long long power(long long base, long long exp) {
    long long res = 1, mod = 1000000007;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) 
            res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

long long modInverse(long long n) {
    return power(n, 1000000007 - 2);
}

typedef struct {
    int l, r, v;
} Query;

typedef struct {
    int idx;
    long long val;
} Event;

int compareEvents(const void* a, const void* b) {
    return ((Event*)a)->idx - ((Event*)b)->idx;
}

int xorAfterQueries(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize) {
    long long MOD = 1000000007;
    int n = numsSize;
    int square = (int)sqrt(n) + 1;
    
    long long* numL = (long long*)malloc(n * sizeof(long long));
    long long* factors = (long long*)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        numL[i] = nums[i];
        factors[i] = 1;
    }

    Query** small_k_queries = (Query**)calloc(square, sizeof(Query*));
    int* small_k_counts = (int*)calloc(square, sizeof(int));
    int* small_k_capacities = (int*)calloc(square, sizeof(int));

    for (int i = 0; i < queriesSize; i++) {
        int l = queries[i][0], r = queries[i][1], k = queries[i][2], v = queries[i][3];
        if (k >= square) {
            for (int idx = l; idx <= r; idx += k) {
                numL[idx] = (numL[idx] * v) % MOD;
            }
        } else {
            if (small_k_counts[k] == small_k_capacities[k]) {
                small_k_capacities[k] = small_k_capacities[k] == 0 ? 10 : small_k_capacities[k] * 2;
                small_k_queries[k] = (Query*)realloc(small_k_queries[k], small_k_capacities[k] * sizeof(Query));
            }
            small_k_queries[k][small_k_counts[k]].l = l;
            small_k_queries[k][small_k_counts[k]].r = r;
            small_k_queries[k][small_k_counts[k]].v = v;
            small_k_counts[k]++;
        }
    }

    for (int k = 1; k < square; k++) {
        if (small_k_counts[k] == 0) 
            continue;

        Event** events = (Event**)calloc(k, sizeof(Event*));
        int* e_counts = (int*)calloc(k, sizeof(int));
        int* e_caps = (int*)calloc(k, sizeof(int));

        for (int i = 0; i < small_k_counts[k]; i++) {
            int l = small_k_queries[k][i].l;
            int r = small_k_queries[k][i].r;
            int v = small_k_queries[k][i].v;
            int rem = l % k;
            int last = l + ((r - l) / k) * k;

            if (e_counts[rem] == e_caps[rem]) {
                e_caps[rem] = e_caps[rem] == 0 ? 4 : e_caps[rem] * 2;
                events[rem] = (Event*)realloc(events[rem], e_caps[rem] * sizeof(Event));
            }
            events[rem][e_counts[rem]].idx = l;
            events[rem][e_counts[rem]].val = v;
            e_counts[rem]++;

            if (last + k < n) {
                if (e_counts[rem] == e_caps[rem]) {
                    e_caps[rem] = e_caps[rem] == 0 ? 4 : e_caps[rem] * 2;
                    events[rem] = (Event*)realloc(events[rem], e_caps[rem] * sizeof(Event));
                }
                events[rem][e_counts[rem]].idx = last + k;
                events[rem][e_counts[rem]].val = modInverse(v);
                e_counts[rem]++;
            }
        }

        for (int rem = 0; rem < k; rem++) {
            if (e_counts[rem] == 0) 
                continue;
            qsort(events[rem], e_counts[rem], sizeof(Event), compareEvents);
            
            long long current_factor = 1;
            int ptr = 0;
            for (int i = rem; i < n; i += k) {
                while (ptr < e_counts[rem] && events[rem][ptr].idx == i) {
                    current_factor = (current_factor * events[rem][ptr].val) % MOD;
                    ptr++;
                }
                factors[i] = (factors[i] * current_factor) % MOD;
            }
            free(events[rem]);
        }
        free(events); free(e_counts); free(e_caps);
        free(small_k_queries[k]);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans ^= (int)((numL[i] * factors[i]) % MOD);
    }

    free(numL); free(factors);
    free(small_k_queries); free(small_k_counts); free(small_k_capacities);
    return ans;
}