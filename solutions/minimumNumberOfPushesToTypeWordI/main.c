#include <stdlib.h>
#include <string.h>
 
int compare(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int minimumPushes(char* word) { 
    int charCount[26] = {0};
    for(int i = 0; word[i] != '\0'; i++) {
        charCount[word[i] - 'a']++;
    }
 
    int frequencies[26];
    int freqCount = 0;
    for(int i = 0; i < 26; i++) {
        if(charCount[i] > 0) {
            frequencies[freqCount++] = charCount[i];
        }
    }
 
    qsort(frequencies, freqCount, sizeof(int), compare);
 
    int minPushCount = 0;
    for(int i = 0; i < freqCount; i++) {
        int presses = (i / 8) + 1;  // Quantas vezes pressionar
        minPushCount += frequencies[i] * presses;
    }

    return minPushCount;
}