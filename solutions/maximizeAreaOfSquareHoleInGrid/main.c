#include <stdlib.h>
#include <string.h>

static int cmpInt(const void* a, const void* b) {
    int x = *(const int*)a;
    int y = *(const int*)b;
    return (x > y) - (x < y);
}

static int findLongestConsecutive(int* bars, int barsSize) {
    if (barsSize == 0) return 0;
    
    int longest = 1;
    int current = 1;
    
    for (int i = 1; i < barsSize; i++) {
        if (bars[i] == bars[i - 1] + 1) {
            current++;
            if (current > longest) {
                longest = current;
            }
        } else if (bars[i] != bars[i - 1]) {
            current = 1;
        }
    }
    
    return longest;
}

int maximizeSquareHoleArea(int n, int m, int* hBars, int hBarsSize, 
                           int* vBars, int vBarsSize) {
    (void)n;
    (void)m;
    
   
    if (hBarsSize == 0 || vBarsSize == 0) {
        return 1;
    }
    
    int* hBarsCopy = (int*)malloc(hBarsSize * sizeof(int));
    int* vBarsCopy = (int*)malloc(vBarsSize * sizeof(int));
    
    if (!hBarsCopy || !vBarsCopy) {
        free(hBarsCopy);
        free(vBarsCopy);
        return 1;
    }
    
    memcpy(hBarsCopy, hBars, hBarsSize * sizeof(int));
    memcpy(vBarsCopy, vBars, vBarsSize * sizeof(int));
    
    qsort(hBarsCopy, hBarsSize, sizeof(int), cmpInt);
    qsort(vBarsCopy, vBarsSize, sizeof(int), cmpInt);
    
    int hConsecutive = findLongestConsecutive(hBarsCopy, hBarsSize);
    int vConsecutive = findLongestConsecutive(vBarsCopy, vBarsSize);
    
    free(hBarsCopy);
    free(vBarsCopy);
    
    int side = 1 + (hConsecutive < vConsecutive ? hConsecutive : vConsecutive);
    
    return side * side;
}