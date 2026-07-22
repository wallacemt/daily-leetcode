#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

/* ==================== SEGMENT TREE ==================== */
typedef struct {
    int *tree;
    int n, cap, ident;
    int (*merge)(int, int);
} SegTree;

static inline int imax(int a, int b) { return a > b ? a : b; }

static void seg_init(SegTree *s, const int *a, int n, int ident,
                     int (*merge)(int, int)) {
    int cap = 1;
    while (cap < n) cap <<= 1;
    
    s->n = n;
    s->cap = cap;
    s->ident = ident;
    s->merge = merge;
    s->tree = malloc((size_t)2 * cap * sizeof(int));
    
    for (int i = 0; i < cap; i++)
        s->tree[cap + i] = (i < n) ? a[i] : ident;
    
    for (int i = cap - 1; i >= 1; i--)
        s->tree[i] = merge(s->tree[2*i], s->tree[2*i+1]);
}

static inline int seg_query(SegTree *s, int l, int r) {
    if (l > r) return s->ident;
    
    int resl = s->ident, resr = s->ident;
    int lo = s->cap + l, hi = s->cap + r + 1;
    
    for (; lo < hi; lo >>= 1, hi >>= 1) {
        if (lo & 1) resl = s->merge(resl, s->tree[lo++]);
        if (hi & 1) resr = s->merge(s->tree[--hi], resr);
    }
    return s->merge(resl, resr);
}

static inline void seg_free(SegTree *s) {
    free(s->tree);
    s->tree = NULL;
}

/* ==================== ZERO-RUN EXTRACTION ==================== */
typedef struct {
    int *starts;
    int *ends;
    int *run_idx;  /* Mapa: posição -> índice do run (para O(1) lookup) */
    int count;
    int total_ones;
} ZeroRuns;

static ZeroRuns extract_zero_runs(const char *s, int n) {
    ZeroRuns runs = {0};
    runs.starts = malloc(n * sizeof(int));
    runs.ends = malloc(n * sizeof(int));
    runs.run_idx = malloc(n * sizeof(int));
    
    /* Inicializa mapa com -1 */
    for (int i = 0; i < n; i++)
        runs.run_idx[i] = -1;
    
    int current_run = -1;
    
    for (int i = 0; i < n; i++) {
        if (s[i] == '0') {
            if (i == 0 || s[i-1] == '1') {
                runs.starts[runs.count] = i;
                current_run = runs.count;
                runs.count++;
            }
            runs.ends[current_run] = i;
            runs.run_idx[i] = current_run;  /* Mapa: posição -> run */
        } else {
            runs.total_ones++;
        }
    }
    
    return runs;
}

static void zero_runs_free(ZeroRuns *runs) {
    free(runs->starts);
    free(runs->ends);
    free(runs->run_idx);
}

/* ==================== OPTIMIZED QUERY PROCESSING ==================== */
int *maxActiveSectionsAfterTrade(char *s, int **queries, int q,
                                 int *qcols, int *returnSize) {
    if (!s || !queries || q <= 0) {
        *returnSize = 0;
        return NULL;
    }
    
    int n = (int)strlen(s);
    if (n == 0) {
        *returnSize = 0;
        return NULL;
    }
    
    /* Extrai runs de zeros com mapa O(1) */
    ZeroRuns runs = extract_zero_runs(s, n);
    
    int *ans = malloc(q * sizeof(int));
    *returnSize = q;
    
    /* Caso trivial: menos de 2 runs */
    if (runs.count < 2) {
        for (int i = 0; i < q; i++)
            ans[i] = runs.total_ones;
        zero_runs_free(&runs);
        return ans;
    }
    
    /* Computa gaps */
    int *gaps = malloc((runs.count - 1) * sizeof(int));
    for (int i = 0; i < runs.count - 1; i++) {
        int len_i = runs.ends[i] - runs.starts[i] + 1;
        int len_next = runs.ends[i+1] - runs.starts[i+1] + 1;
        gaps[i] = len_i + len_next;
    }
    
    /* Constrói segment tree para RMQ */
    SegTree seg;
    seg_init(&seg, gaps, runs.count - 1, INT_MIN, imax);
    
    /* ==================== PROCESSAMENTO DE QUERIES ==================== */
    for (int i = 0; i < q; i++) {
        int l = queries[i][0];
        int r = queries[i][1];
        
        /* Snap para zeros mais próximos */
        while (l < n && s[l] == '1') l++;
        while (r >= 0 && s[r] == '1') r--;
        
        if (l > r) {
            ans[i] = runs.total_ones;
            continue;
        }
        
        /* O(1) lookup: encontra runs usando mapa */
        int a = runs.run_idx[l];
        int b = runs.run_idx[r];
        
        if (a == -1 || b == -1) {
            ans[i] = runs.total_ones;
            continue;
        }
        
        int len_a = runs.ends[a] - runs.starts[a] + 1;
        int len_b = runs.ends[b] - runs.starts[b] + 1;
        
        bool clip_a = (runs.starts[a] < l);
        bool clip_b = (runs.ends[b] > r);
        
        int eff_a = clip_a ? (runs.ends[a] - l + 1) : len_a;
        int eff_b = clip_b ? (r - runs.starts[b] + 1) : len_b;
        
        int gain;
        
        if (a == b) {
            /* Mesmo run: sem gap */
            gain = 0;
        } else if (a + 1 == b) {
            /* Gap único: soma ambos */
            gain = eff_a + eff_b;
        } else {
            /* Múltiplos gaps: usa segment tree */
            int gl = clip_a ? a + 1 : a;
            int gr = clip_b ? b - 2 : b - 1;
            
            gain = (gl <= gr) ? seg_query(&seg, gl, gr) : INT_MIN;
            
            if (clip_a && a + 1 < b) {
                int cand = eff_a + (runs.ends[a+1] - runs.starts[a+1] + 1);
                if (cand > gain) gain = cand;
            }
            if (clip_b && b - 1 > a) {
                int cand = (runs.ends[b-1] - runs.starts[b-1] + 1) + eff_b;
                if (cand > gain) gain = cand;
            }
        }
        
        if (gain < 0) gain = 0;
        ans[i] = runs.total_ones + gain;
    }
    
    seg_free(&seg);
    free(gaps);
    zero_runs_free(&runs);
    
    return ans;
}