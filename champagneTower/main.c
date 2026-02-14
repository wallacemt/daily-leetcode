#include <math.h>
#include <stdlib.h>

double champagneTower(int poured, int query_row, int query_glass) {
    double *current = (double *)calloc(query_row + 1, sizeof(double));
    double *next = (double *)calloc(query_row + 1, sizeof(double));
    
    current[0] = (double)poured;
    
    for (int r = 0; r < query_row; ++r) {
        for (int c = 0; c <= r; ++c) {
            double q = (current[c] - 1.0) / 2.0;
            if (q > 0) {
                next[c] += q;
                next[c + 1] += q;
            }
        }
        
        double *temp = current;
        current = next;
        next = temp;
        memset(next, 0, sizeof(double) * (query_row + 1));
    }
    
    double result = fmin(1.0, current[query_glass]);
    
    free(current);
    free(next);
    
    return result;
}