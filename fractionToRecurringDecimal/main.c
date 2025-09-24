#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    long long rem;
    int pos;
} MapEntry;

char* fractionToDecimal(int numerator, int denominator) {
    if (numerator == 0) return "0";
    char* res = malloc(10000);
    int idx = 0;
    if ((numerator < 0) ^ (denominator < 0)) res[idx++] = '-';
    long long n = llabs((long long)numerator), d = llabs((long long)denominator);
    idx += sprintf(res + idx, "%lld", n / d);
    long long rem = n % d;
    if (rem == 0) { res[idx] = '\0'; return res; }
    res[idx++] = '.';
    
    MapEntry* map = malloc(sizeof(MapEntry) * 10000);
    int mapSize = 0;
    
    while (rem) {
        for (int i = 0; i < mapSize; i++) {
            if (map[i].rem == rem) {
                int pos = map[i].pos;
                for (int j = idx; j >= pos; j--) {
                    res[j + 1] = res[j];
                }
                res[pos] = '(';
                res[idx + 1] = ')';
                res[idx + 2] = '\0';
                free(map);
                return res;
            }
        }
        map[mapSize].rem = rem;
        map[mapSize].pos = idx;
        mapSize++;
        rem *= 10;
        res[idx++] = (rem / d) + '0';
        rem %= d;
    }
    res[idx] = '\0';
    free(map);
    return res;
}