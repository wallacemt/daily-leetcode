static int cmpInt(const void* a, const void* b){
    int x = *(const int*)a, y = *(const int*)b;
    return (x > y) - (x < y);
}

int** minimumAbsDifference(int* arr, int arrSize, int* returnSize, int** returnColumnSizes) {
    qsort(arr, arrSize, sizeof(int), cmpInt);
    
    int min_diff = INT_MAX;
    for (int i = 0; i < arrSize - 1; i++){
        int diff = arr[i + 1] - arr[i];
        if (diff < min_diff){
            min_diff = diff;
        }
    }
    
    // Alocar com tamanho máximo possível
    int** res = (int**)malloc(sizeof(int*) * arrSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * arrSize);
    
    int count = 0;
    for (int i = 0; i < arrSize - 1; i++){
        if (arr[i + 1] - arr[i] == min_diff){
            res[count] = (int*)malloc(sizeof(int) * 2);
            res[count][0] = arr[i];
            res[count][1] = arr[i + 1];
            (*returnColumnSizes)[count] = 2;
            count++;
        }
    }
    
    *returnSize = count;
    return res;
}
