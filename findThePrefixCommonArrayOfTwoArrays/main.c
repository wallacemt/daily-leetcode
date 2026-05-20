
int* findThePrefixCommonArray(int* A, int ASize, int* B, int BSize, int* returnSize) {
    int n = ASize;
    int* res = (int*)malloc(sizeof(int) * n);
    int count[51] = {0};  
    int common = 0;
    
    for (int i = 0; i < n; i++) {
        // Processar A[i]
        if (++count[A[i]] == 2) {
            common++;
        }
        
        // Processar B[i]
        if (++count[B[i]] == 2) {
            common++;
        }
        
        res[i] = common;
    }
    
    *returnSize = n;
    return res;
}