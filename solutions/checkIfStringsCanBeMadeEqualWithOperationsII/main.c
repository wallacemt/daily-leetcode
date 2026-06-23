#define MAX_CHAR 256
bool checkStrings(char* s1, char* s2) {
    int odds_s1[MAX_CHAR] = {0}, evens_s1[MAX_CHAR] = {0};
    int odds_s2[MAX_CHAR] = {0}, evens_s2[MAX_CHAR] = {0};

    for (int i = 1; i < strlen(s1); i += 2) {
        odds_s1[s1[i]]++;
    }
    for (int i = 0; i < strlen(s1); i += 2) {
        evens_s1[s1[i]]++;
    }

    for (int i = 1; i < strlen(s2); i += 2) {
        odds_s2[s2[i]]++;
    }
    for (int i = 0; i < strlen(s2); i += 2) {
        evens_s2[s2[i]]++;
    }

    for (int i = 0; i < MAX_CHAR; i++) {
        if (odds_s1[i] != odds_s2[i] || evens_s1[i] != evens_s2[i]) {
            return 0; 
        }
    }
    return 1; 
}