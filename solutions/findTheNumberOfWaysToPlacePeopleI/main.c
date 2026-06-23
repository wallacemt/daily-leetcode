int numberOfPairs(int** points, int pointsSize, int* pointsColSize) {
    int count = 0;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = 0; j < pointsSize; j++) {
            if (i == j) continue;
            
            int ax = points[i][0], ay = points[i][1];
            int bx = points[j][0], by = points[j][1];
        
            if (ax <= bx && ay >= by && (ax < bx || ay > by)) {
                int valid = 1;
                
                for (int k = 0; k < pointsSize; k++) {
                    if (k == i || k == j) continue;
                    
                    int kx = points[k][0], ky = points[k][1];
                    
                    if (kx >= ax && kx <= bx && ky >= by && ky <= ay) {
                        valid = 0;
                        break;
                    }
                }
                
                if (valid) {
                    count++;
                }
            }
        }
    }
    
    return count;
}
