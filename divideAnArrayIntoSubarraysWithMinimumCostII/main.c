typedef long long ll;

static int cmpInt(const void* a, const void* b){
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static inline void bitAdd(ll* bit, int n, int idx, ll delta){
    for (; idx <= n; idx += idx & -idx) 
        bit[idx] += delta;
}

static inline ll bitSum(ll* bit, int idx){
    ll s = 0;
    for (; idx > 0; idx -= idx & -idx) 
        s += bit[idx];
    return s;
}

static int bitKthFast(ll* bitCnt, int n, ll k){
    int idx = 0;
    for (int step = 1 << 20; step > 0; step >>= 1){
        int nxt = idx + step;
        if (nxt <= n && bitCnt[nxt] < k){
            idx = nxt;
            k -= bitCnt[nxt];
        }
    }
    return idx + 1;
}

static ll sumKSmallest(ll* bitCnt, ll* bitSumArr, int* vals, int m, int k){
    if (k <= 0) 
        return 0;
    int idx = bitKthFast(bitCnt, m, (ll)k);         
    ll cntLess = bitSum(bitCnt, idx - 1);
    ll sumLess = bitSum(bitSumArr, idx - 1);
    ll need = (ll)k - cntLess;
    ll v = (ll)vals[idx - 1];                   
    return sumLess + need * v;
}

static inline int lowerBound(int* vals, int m, int x){
    int l = 0, r = m;
    while (l < r){
        int mid = (l + r) >> 1;
        if (vals[mid] < x) 
            l = mid + 1;
        else r = mid;
    }
    return l;
}

long long minimumCost(int* nums, int numsSize, int k, int dist) {
    ll base = (ll)nums[0];
    int kSmall = k - 1;             
    if (kSmall <= 0) 
        return base;

    int aSize = numsSize - 1;
    int* a = nums + 1;

    int winSize = dist + 1;
    if (winSize > aSize) 
        return -1;

    int vals_stack[256];
    int* vals = (aSize <= 256) ? vals_stack : (int*)malloc(sizeof(int) * aSize);
    memcpy(vals, a, sizeof(int) * aSize);
    qsort(vals, aSize, sizeof(int), cmpInt);

    int m = 1;
    for (int i = 1; i < aSize; i++){
        if (vals[i] != vals[i - 1]){
            vals[m++] = vals[i];
        }
    }

    ll* bitCnt = (ll*)calloc(m + 1, sizeof(ll));
    ll* bitSumArr = (ll*)calloc(m + 1, sizeof(ll));

    int* posCache = (int*)malloc(sizeof(int) * aSize);
    for (int i = 0; i < aSize; i++){
        posCache[i] = lowerBound(vals, m, a[i]) + 1;
    }

    for (int i = 0; i < winSize; i++){
        bitAdd(bitCnt, m, posCache[i], 1);
        bitAdd(bitSumArr, m, posCache[i], (ll)a[i]);
    }

    ll res = LLONG_MAX;

    for (int l = 0; l + dist < aSize; l++){
        ll sumSmall = sumKSmallest(bitCnt, bitSumArr, vals, m, kSmall);
        ll cur = base + sumSmall;
        if (cur < res) 
            res = cur;

        if (l + dist + 1 >= aSize) 
            break;

        int posOut = posCache[l];
        int posIn = posCache[l + dist + 1];
        bitAdd(bitCnt, m, posOut, -1);
        bitAdd(bitSumArr, m, posOut, -(ll)a[l]);
        bitAdd(bitCnt, m, posIn, 1);
        bitAdd(bitSumArr, m, posIn, (ll)a[l + dist + 1]);
    }

    free(bitCnt);
    free(bitSumArr);
    free(posCache);
    if (aSize > 256) 
        free(vals);

    return res;
}