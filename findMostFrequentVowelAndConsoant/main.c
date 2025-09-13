#include <stdio.h>
#include <string.h>

int max(int a, int b) {
    return a > b ? a : b;
}
int maxFreqSum(char* s) {
    char* vowels = "aeiou";
    int vowelCount[5] = {0};      
    int consonantCount[26] = {0}; 
    
    for (int i = 0; i < strlen(s); i++) {
        char* vowelPos = strchr(vowels, s[i]);
        if (vowelPos != NULL) {
            int vowelIndex = vowelPos - vowels;
            vowelCount[vowelIndex]++;
        } else {
            consonantCount[s[i] - 'a']++;
        }
    }
    
    int maxVowel = 0, maxConsonant = 0;
    for (int i = 0; i < 5; i++) {
        maxVowel = max(maxVowel, vowelCount[i]);
    }
    for (int i = 0; i < 26; i++) {
        maxConsonant = max(maxConsonant, consonantCount[i]);
    }
    
    return maxVowel + maxConsonant;
}
