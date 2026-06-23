int canBeTypedWords(char* text, char* brokenLetters) {
    bool broken[26] = {false};
    for (int i = 0; brokenLetters[i] != '\0'; i++) {
        broken[brokenLetters[i] - 'a'] = true;
    }   
    int count = 0;
    int i = 0;
    int textLen = strlen(text);
    while (i < textLen) {
        bool canType = true;
        
        while (i < textLen && text[i] != ' ') {
            if (broken[text[i] - 'a']) {
                canType = false;
            }
            i++;
        }
        if (canType) {
            count++;
        }
        if (i < textLen && text[i] == ' ') {
            i++;
        }
    }
    return count;
}