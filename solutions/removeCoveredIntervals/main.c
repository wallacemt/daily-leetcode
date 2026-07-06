int cmp(const void *a, const void *b) {
    int *arrA = *(int**)a;
    int *arrB = *(int**)b;
     
    if (arrA[0] != arrB[0]) {
        return arrA[0] - arrB[0];
    }
     
    if (arrA[1] > arrB[1]) return -1;
    if (arrA[1] < arrB[1]) return 1;
    return 0;
}

int removeCoveredIntervals(int** intervals, int intervalsSize, 
                           int* intervalsColSize) {
    qsort(intervals, intervalsSize, sizeof(int*), cmp);
    
  
    int maxEnd = intervals[0][1];
    
    for (int i = 1; i < intervalsSize; i++) {
        if (maxEnd < intervals[i][1]) {
            maxEnd = intervals[i][1];
            ret++;
        }
    }
    
    return ret;
}