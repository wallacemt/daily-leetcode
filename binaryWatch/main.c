#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int countSetBits(int n) {
    int cnt = 0;
    while (n > 0) {
        n &= (n - 1);
        cnt++;
    }
    return cnt;
}

char** readBinaryWatch(int turnedOn, int* returnSize) {
    char** res = (char**)malloc(720 * sizeof(char*));
    *returnSize = 0;

    // Pré-computar set bits para horas e minutos
    int hourBits[12];
    int minuteBits[60];

    for (int i = 0; i < 12; i++) {
        hourBits[i] = countSetBits(i);
    }

    for (int i = 0; i < 60; i++) {
        minuteBits[i] = countSetBits(i);
    }

    // Iterar sobre horas e minutos
    for (int h = 0; h < 12; h++) {
        if (hourBits[h] > turnedOn) continue; // Pula se já excedeu
        
        int neededMinuteBits = turnedOn - hourBits[h];
        
        for (int m = 0; m < 60; m++) {
            if (minuteBits[m] == neededMinuteBits) {
                res[*returnSize] = (char*)malloc(6 * sizeof(char));
                sprintf(res[*returnSize], "%d:%02d", h, m);
                (*returnSize)++;
            }
        }
    }

    return res;
}
