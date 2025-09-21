#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAXMOVIE 100005

typedef struct AvNode {
    int price;
    int shop;
    unsigned pr;
    struct AvNode *l, *r;
} AvNode;

typedef struct RNode {
    int price;
    int shop;
    int movie;
    unsigned pr;
    struct RNode *l, *r;
} RNode;

static inline int cmp_av(int p1, int s1, int p2, int s2) {
    if (p1 != p2) return (p1 < p2) ? -1 : 1;
    if (s1 != s2) return (s1 < s2) ? -1 : 1;
    return 0;
}

static inline int cmp_r(int p1, int s1, int m1, int p2, int s2, int m2) {
    if (p1 != p2) return (p1 < p2) ? -1 : 1;
    if (s1 != s2) return (s1 < s2) ? -1 : 1;
    if (m1 != m2) return (m1 < m2) ? -1 : 1;
    return 0;
}

static AvNode* av_merge(AvNode* a, AvNode* b) {
    if (!a) return b;
    if (!b) return a;
    if (a -> pr < b -> pr) {
        a -> r = av_merge(a -> r, b);
        return a;
    } else {
        b -> l = av_merge(a, b -> l);
        return b;
    }
}

static void av_split(AvNode* root, int price, int shop, AvNode** left, AvNode** right) {
    if (!root) { *left = *right = NULL; return; }
    if (cmp_av(root -> price, root -> shop, price, shop) < 0) {
        av_split(root -> r, price, shop, &root -> r, right);
        *left = root;
    } else {
        av_split(root -> l, price, shop, left, &root -> l);
        *right = root;
    }
}

static AvNode* av_insert(AvNode* root, AvNode* node) {
    if (!root) return node;
    if (node -> pr < root -> pr) {
        AvNode *l, *r;
        av_split(root, node -> price, node -> shop, &l, &r);
        node -> l = l; node -> r = r;
        return node;
    } else {
        if (cmp_av(node -> price, node -> shop, root -> price, root -> shop) < 0)
            root -> l = av_insert(root -> l, node);
        else
            root -> r = av_insert(root -> r, node);
        return root;
    }
}

static AvNode* av_erase(AvNode* root, int price, int shop) {
    if (!root) return NULL;
    int c = cmp_av(price, shop, root -> price, root -> shop);
    if (c == 0) {
        AvNode* t = av_merge(root -> l, root -> r);
        free(root);
        return t;
    } else if (c < 0) {
        root -> l = av_erase(root -> l, price, shop);
    } else {
        root -> r = av_erase(root -> r, price, shop);
    }
    return root;
}

static void av_collect_k(AvNode* root, int *out, int *cnt, int k) {
    if (!root || *cnt >= k) return;
    av_collect_k(root -> l, out, cnt, k);
    if (*cnt < k) {
        out[(*cnt)++] = root -> shop;
    }
    if (*cnt < k) av_collect_k(root -> r, out, cnt, k);
}

static void av_free(AvNode* root) {
    if (!root) return;
    av_free(root -> l);
    av_free(root -> r);
    free(root);
}

static RNode* r_merge(RNode* a, RNode* b) {
    if (!a) return b;
    if (!b) return a;
    if (a -> pr < b -> pr) {
        a -> r = r_merge(a -> r, b);
        return a;
    } else {
        b -> l = r_merge(a, b -> l);
        return b;
    }
}

static void r_split(RNode* root, int price, int shop, int movie, RNode** left, RNode** right) {
    if (!root) { *left = *right = NULL; return; }
    if (cmp_r(root -> price, root -> shop, root -> movie, price, shop, movie) < 0) {
        r_split(root -> r, price, shop, movie, &root -> r, right);
        *left = root;
    } else {
        r_split(root -> l, price, shop, movie, left, &root -> l);
        *right = root;
    }
}

static RNode* r_insert(RNode* root, RNode* node) {
    if (!root) return node;
    if (node -> pr < root -> pr) {
        RNode *l, *r;
        r_split(root, node -> price, node -> shop, node -> movie, &l, &r);
        node -> l = l; node -> r = r;
        return node;
    } else {
        if (cmp_r(node -> price, node -> shop, node -> movie, root -> price, root -> shop, root -> movie) < 0)
            root -> l = r_insert(root -> l, node);
        else
            root -> r = r_insert(root -> r, node);
        return root;
    }
}

static RNode* r_erase(RNode* root, int price, int shop, int movie) {
    if (!root) return NULL;
    int c = cmp_r(price, shop, movie, root -> price, root -> shop, root -> movie);
    if (c == 0) {
        RNode* t = r_merge(root -> l, root -> r);
        free(root);
        return t;
    } else if (c < 0) {
        root -> l = r_erase(root -> l, price, shop, movie);
    } else {
        root -> r = r_erase(root -> r, price, shop, movie);
    }
    return root;
}

static void r_collect_k(RNode* root, int (*out)[2], int *cnt, int k) {
    if (!root || *cnt >= k) return;
    r_collect_k(root -> l, out, cnt, k);
    if (*cnt < k) {
        out[*cnt][0] = root -> shop;
        out[*cnt][1] = root -> movie;
        (*cnt)++;
    }
    if (*cnt < k) r_collect_k(root -> r, out, cnt, k);
}

static void r_free(RNode* root) {
    if (!root) return;
    r_free(root -> l);
    r_free(root -> r);
    free(root);
}

typedef struct {
    uint64_t *keys;
    int *vals;
    unsigned char *used;
    size_t cap;
    size_t mask;
} HashMap;

static size_t nextPow2(size_t x) {
    size_t p = 1;
    while (p < x) p <<= 1;
    return p;
}

static HashMap* hashmapCreate(size_t expected) {
    size_t cap = nextPow2(expected * 2 + 8);
    HashMap* m = (HashMap*)malloc(sizeof(HashMap));
    m -> cap = cap;
    m -> mask = cap - 1;
    m -> keys = (uint64_t*)malloc(sizeof(uint64_t) * cap);
    m -> vals = (int*)malloc(sizeof(int) * cap);
    m -> used = (unsigned char*)malloc(sizeof(unsigned char) * cap);
    memset(m -> used, 0, cap);
    return m;
}

static void hashmapPut(HashMap* m, uint64_t key, int val) {
    uint64_t h = key * 11400714819323198485ull;
    size_t idx = (size_t)h & m -> mask;
    while (m -> used[idx]) {
        if (m -> keys[idx] == key) { m -> vals[idx] = val; return; }
        idx = (idx + 1) & m -> mask;
    }
    m -> used[idx] = 1;
    m -> keys[idx] = key;
    m -> vals[idx] = val;
}

static int hashmapGet(HashMap* m, uint64_t key) {
    uint64_t h = key * 11400714819323198485ull;
    size_t idx = (size_t)h & m -> mask;
    size_t start = idx;
    while (m -> used[idx]) {
        if (m -> keys[idx] == key) return m -> vals[idx];
        idx = (idx + 1) & m -> mask;
        if (idx == start) break;
    }
    return -1;
}

typedef struct {
    int n;
    int m;
    HashMap *priceMap;      
    AvNode **available;    
    RNode *rentedRoot;      
} MovieRentingSystem;

static AvNode* new_avnode(int price, int shop) {
    AvNode* p = (AvNode*)malloc(sizeof(AvNode));
    p -> price = price; p -> shop = shop; p -> pr = ((unsigned)rand()<<16) ^ (unsigned)rand();
    p -> l = p -> r = NULL;
    return p;
}

static RNode* new_rnode(int price, int shop, int movie) {
    RNode* p = (RNode*)malloc(sizeof(RNode));
    p -> price = price; p -> shop = shop; p -> movie = movie; p -> pr = ((unsigned)rand()<<16) ^ (unsigned)rand();
    p -> l = p -> r = NULL;
    return p;
}

MovieRentingSystem* movieRentingSystemCreate(int n, int** entries, int entriesSize, int* entriesColSize) {
    srand(1234567);
    MovieRentingSystem* obj = (MovieRentingSystem*)malloc(sizeof(MovieRentingSystem));
    obj -> n = n;
    obj -> m = entriesSize;
    obj -> priceMap = hashmapCreate((size_t)entriesSize + 4);
    obj -> available = (AvNode**)calloc(MAXMOVIE, sizeof(AvNode*));
    obj -> rentedRoot = NULL;
    for (int i = 0; i < entriesSize; ++i) {
        int shop = entries[i][0];
        int movie = entries[i][1];
        int price = entries[i][2];
        uint64_t key = (((uint64_t)movie) << 32) | (uint32_t)shop;
        hashmapPut(obj -> priceMap, key, price);
        AvNode* node = new_avnode(price, shop);
        obj -> available[movie] = av_insert(obj -> available[movie], node);
    }
    return obj;
}

int* movieRentingSystemSearch(MovieRentingSystem* obj, int movie, int* retSize) {
    int *res = (int*)malloc(sizeof(int) * 5);
    *retSize = 0;
    if (!obj) return res;
    if (movie < 0 || movie >= MAXMOVIE) return res;
    AvNode* root = obj -> available[movie];
    if (!root) return res;
    av_collect_k(root, res, retSize, 5);
    return res;
}

void movieRentingSystemRent(MovieRentingSystem* obj, int shop, int movie) {
    if (!obj) return;
    uint64_t key = (((uint64_t)movie) << 32) | (uint32_t)shop;
    int price = hashmapGet(obj -> priceMap, key);
    if (price < 0) return;
    obj -> available[movie] = av_erase(obj -> available[movie], price, shop);
    RNode* rn = new_rnode(price, shop, movie);
    obj -> rentedRoot = r_insert(obj -> rentedRoot, rn);
}

void movieRentingSystemDrop(MovieRentingSystem* obj, int shop, int movie) {
    if (!obj) return;
    uint64_t key = (((uint64_t)movie) << 32) | (uint32_t)shop;
    int price = hashmapGet(obj -> priceMap, key);
    if (price < 0) return;
    obj -> rentedRoot = r_erase(obj -> rentedRoot, price, shop, movie);
    AvNode* an = new_avnode(price, shop);
    obj -> available[movie] = av_insert(obj -> available[movie], an);
}

int** movieRentingSystemReport(MovieRentingSystem* obj, int* retSize, int** retColSize) {
    int **res = (int**)malloc(sizeof(int*) * 5);
    *retColSize = (int*)malloc(sizeof(int) * 5);
    *retSize = 0;
    if (!obj) return res;
    int buf[5][2];
    int cnt = 0;
    r_collect_k(obj -> rentedRoot, buf, &cnt, 5);
    for (int i = 0; i < cnt; ++i) {
        res[i] = (int*)malloc(sizeof(int) * 2);
        res[i][0] = buf[i][0];
        res[i][1] = buf[i][1];
        (*retColSize)[i] = 2;
        (*retSize)++;
    }
    return res;
}

void movieRentingSystemFree(MovieRentingSystem* obj) {
    if (!obj) return;
    if (obj -> available) {
        for (int i = 0; i < MAXMOVIE; ++i) if (obj -> available[i]) av_free(obj -> available[i]);
        free(obj -> available);
    }
    if (obj -> rentedRoot) r_free(obj -> rentedRoot);
    if (obj -> priceMap) {
        free(obj -> priceMap -> keys);
        free(obj -> priceMap -> vals);
        free(obj -> priceMap -> used);
        free(obj -> priceMap);
    }
    free(obj);
}