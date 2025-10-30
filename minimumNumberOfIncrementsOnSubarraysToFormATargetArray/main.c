int minNumberOperations(int* target, int targetSize) {
    if (targetSize == 0) return 0;
    
    int operations = target[0]; 
    
    for (int i = 1; i < targetSize; i++) {
        if (target[i] > target[i - 1]) {
            operations += target[i] - target[i - 1];
        }
    }
    
    return operations;
}
