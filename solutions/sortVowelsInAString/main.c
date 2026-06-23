int compare(const void* a, const void* b) {
    return (*(char*)a - *(char*)b);
}

char* sortVowels(char* s) {
    int len = strlen(s);
    char vowelsList[len];
    int vowelCount = 0;
    
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            vowelsList[vowelCount++] = c;
        }
    }
    
    qsort(vowelsList, vowelCount, sizeof(char), compare);
    
    int vowelIndex = 0;
    for (int i = 0; i < len; i++) {
        char c = s[i];
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || 
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            s[i] = vowelsList[vowelIndex++];
        }
    }
    
    return s;
}
