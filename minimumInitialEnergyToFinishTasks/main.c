int compare(const void* a, const void* b) {
    int diffA = (*(int**)a)[1] - (*(int**)a)[0];
    int diffB = (*(int**)b)[1] - (*(int**)b)[0];
    return diffA - diffB;
}

int minimumEffort(int** tasks, int tasksSize, int* tasksColSize) {
    if (tasksSize == 0 || tasks == NULL) return 0;
    
    qsort(tasks, tasksSize, sizeof(int*), compare);
    
    int ans = 0;
    for (int i = 0; i < tasksSize; i++) {
        int* task = tasks[i];
        int effort = task[0];
        int actual = task[1];
        
        ans = (ans + effort > actual) ? (ans + effort) : actual;
    }
    
    return ans;
}