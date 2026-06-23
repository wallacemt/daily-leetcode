double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    double lo = 1e18, hi = -1e18;
    double total = 0.0;
    
    double* y_vals = (double*)malloc(squaresSize * sizeof(double));
    double* l_vals = (double*)malloc(squaresSize * sizeof(double));
    
    for (int i = 0; i < squaresSize; i++) {
        double y = squares[i][1];
        double l = squares[i][2];
        
        y_vals[i] = y;
        l_vals[i] = l;
        
        if (y < lo) lo = y;
        if (y + l > hi) hi = y + l;
        total += l * l;
    }
    
    double target = total / 2.0;
    
    for (int it = 0; it < 80; it++) {
        double mid = (lo + hi) * 0.5;
        double below = 0.0;
        
        for (int i = 0; i < squaresSize; i++) {
            if (mid > y_vals[i]) {
                double h = mid - y_vals[i];
                if (h > l_vals[i]) h = l_vals[i];
                below += h * l_vals[i];
            }
        }
        
        if (below < target) lo = mid;
        else hi = mid;
    }
    
    free(y_vals);
    free(l_vals);
    
    return lo;
}