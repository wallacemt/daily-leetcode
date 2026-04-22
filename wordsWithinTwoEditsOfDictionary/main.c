char** twoEditWords(char** queries, int queriesSize, char** dictionary, 
                    int dictionarySize, int* returnSize) {
    int word_len = strlen(queries[0]);
    
    char** res = (char**)malloc(queriesSize * sizeof(char*));
    int count = 0;

    for (int i = 0; i < queriesSize; i++) {
        char* q = queries[i];
        int found = 0;
        
        for (int k = 0; k < dictionarySize && !found; k++) {
            char* d = dictionary[k];
            
            if (strlen(d) != word_len) 
                continue;
            
            int diff = 0;
            
            for (int j = 0; j < word_len && diff <= 2; j++) {
                if (q[j] != d[j]) 
                    diff++;
            }
            
            if (diff <= 2) {
                res[count++] = q;
                found = 1;  // Sair do loop do dicionário
            }
        }
    }
    
    *returnSize = count;
    return res;
}