int countCollisions(char* directions) {
    int n = 0;
    while (directions[n] != '\0') n++;
    
    if (n == 0) return 0;
    
    int left = 0;
    while (left < n && directions[left] == 'L') {
        left++;
    }
    
    int right = n - 1;
    while (right >= 0 && directions[right] == 'R') {
        right--;
    }
    if (left > right) return 0;
    
    int collisions = 0;
    for (int i = left; i <= right; i++) {
        if (directions[i] != 'S') {
            collisions++;
        }
    }
    
    return collisions;
}
