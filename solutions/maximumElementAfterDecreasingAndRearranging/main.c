int cmp(const void* a, const void* b) {
    int x = *(int*)a;
    int y = *(int*)b;
    return (x > y) - (x < y);
}

int maximumElementAfterDecrementingAndRearranging(int* arr, int arrSize) {
  
    if (arrSize == 0) return 0;
    
    qsort(arr, arrSize, sizeof(int), cmp);

    int res = 1;
    
    for (int i = 0; i < arrSize; i++) {
        if (arr[i] >= res) {
            res++;
        }
    }

    return res - 1;
}