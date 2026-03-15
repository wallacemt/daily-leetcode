#include <stdlib.h>

#define MOD 1000000007
#define MAXN 100005

long long modpow(long long a, long long b){
    long long r = 1;
    a %= MOD;
    while(b){
        if(b & 1) r = r * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return r;
}

typedef struct{
    long long arr[MAXN];
    int sz;
    long long mul, add;
} Fancy;

Fancy* fancyCreate(){
    Fancy* f = malloc(sizeof(Fancy));
    f->sz = 0;
    f->mul = 1;
    f->add = 0;
    return f;
}

void fancyAppend(Fancy* f, int val){
    long long inv = modpow(f->mul, MOD - 2);
    long long v = ((long long)val - f->add) % MOD;
    if(v < 0) v += MOD;
    f->arr[f->sz++] = v * inv % MOD;
}

void fancyAddAll(Fancy* f, int inc){
    f->add = (f->add + (long long)inc) % MOD;
}

void fancyMultAll(Fancy* f, int m){
    f->mul = (long long)f->mul * m % MOD;
    f->add = (long long)f->add * m % MOD;
}

int fancyGetIndex(Fancy* f, int idx){
    if(idx >= f->sz) return -1;
    long long res = (f->arr[idx] * f->mul % MOD + f->add) % MOD;
    return (res < 0) ? res + MOD : res;
}

void fancyFree(Fancy* f){
    free(f);
}