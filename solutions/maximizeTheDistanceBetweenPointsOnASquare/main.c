#include <stdlib.h>
#include <string.h>

int compare(const void* a, const void* b) {
    long long diff = *(const long long*)a - *(const long long*)b;
    return (diff > 0) - (diff < 0);
}

int check(int n, long long* res, int resSize, int side, int k, int* idx) {
    long long perimeter = (long long)side * 4;
    long long curr = res[0];
    idx[0] = 0;

    for (int i = 1; i < k; i++) {
        int l = idx[i - 1] + 1;  // Começar após o índice anterior
        int r = resSize;
        
        while (l < r) {
            int mid = l + (r - l) / 2;
            if (res[mid] < curr + n) 
                l = mid + 1;
            else 
                r = mid;
        }
        
        if (l == resSize) 
            return 0;
        
        idx[i] = l;
        curr = res[l];
    }

    // Verificação direta
    if (res[idx[k - 1]] - res[0] <= perimeter - n) 
        return 1;

    int limit = idx[1];  // Não precisa ir além do segundo índice
    for (idx[0] = 1; idx[0] < limit; idx[0]++) {
        for (int j = 1; j < k; j++) {
            while (idx[j] < resSize && res[idx[j]] < res[idx[j - 1]] + n) {
                idx[j]++;
            }
            if (idx[j] == resSize) 
                return 0;
        }
        if (res[idx[k - 1]] - res[idx[0]] <= perimeter - n) 
            return 1;
    }

    return 0;
}

int maxDistance(int side, int** points, int pointsSize, int* pointsColSize, int k) {
    long long* res = (long long*)malloc(pointsSize * sizeof(long long));
    long long lSide = (long long)side;

    for (int i = 0; i < pointsSize; i++) {
        long long x = points[i][0], y = points[i][1];
        if (x == 0) 
            res[i] = y;
        else if (y == lSide) 
            res[i] = lSide + x;
        else if (x == lSide) 
            res[i] = lSide * 3 - y;
        else 
            res[i] = lSide * 4 - x;
    }

    qsort(res, pointsSize, sizeof(long long), compare);

    int* idx = (int*)malloc(k * sizeof(int));

    int left = 1;
    int right = (int)((lSide * 4) / k) + 1;

    // Busca binária para encontrar a máxima distância mínima
    while (left + 1 < right) {
        int mid = left + (right - left) / 2;
        if (check(mid, res, pointsSize, side, k, idx)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    free(idx);
    free(res);
    
    return left;
}