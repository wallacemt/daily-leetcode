bool isValidRotated(int num) {
    bool hasRotation = false;
    
    while (num > 0) {
        int digit = num % 10;
        
        // Dígitos inválidos (3, 4, 7)
        if (digit == 3 || digit == 4 || digit == 7) {
            return false;
        }
        
        // Dígitos que mudam quando rotacionados (2, 5, 6, 9)
        if (digit == 2 || digit == 5 || digit == 6 || digit == 9) {
            hasRotation = true;
        }
        
        num /= 10;
    }
    
    return hasRotation;
}
int rotatedDigits(int n) {
    int count = 0;
    
    for (int num = 1; num <= n; num++) {
        if (isValidRotated(num)) {
            count++;
        }
    }
    
    return count;
}
