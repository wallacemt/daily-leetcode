bool areAnagrams(const char* str1, const char* str2) {
    int count[26] = {0};

    while (*str1) {
        count[*str1 - 'a']++;
        str1++;
    }

    while (*str2) {
        count[*str2 - 'a']--;
        str2++;
    }

    for (int i = 0; i < 26; i++) {
        if (count[i] != 0) {
            return false;
        }
    }

    return true;
}
char** removeAnagrams(char** words, int wordsSize, int* returnSize) {

    char** result = (char**)malloc(wordsSize * sizeof(char*));
    int count = 0;

    for (int i = 0; i < wordsSize; i++) {
        if (i == 0 || !areAnagrams(words[i], words[i - 1])) {
            result[count++] = words[i];
        }
    }

    *returnSize = count;
    return result;
}