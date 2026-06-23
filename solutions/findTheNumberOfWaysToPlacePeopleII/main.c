#include <stdlib.h>

int compare(const void* a, const void* b) {
    int* pointA = *(int**)a;
    int* pointB = *(int**)b;
    
    if (pointA[0] != pointB[0]) {
        return pointA[0] - pointB[0]; 
    }
    return pointB[1] - pointA[1]; 
}

int numberOfPairs(int** points, int pointsSize, int* pointsColSize) {
 
    int** sortedPoints = (int**)malloc(pointsSize * sizeof(int*));
    for (int i = 0; i < pointsSize; i++) {
        sortedPoints[i] = points[i];
    }
    
    qsort(sortedPoints, pointsSize, sizeof(int*), compare);
    
    int count = 0;
    
    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            int aliceX = sortedPoints[i][0], aliceY = sortedPoints[i][1];
            int bobX = sortedPoints[j][0], bobY = sortedPoints[j][1];
            
            if (aliceY < bobY) continue;
            
            int valid = 1;
            for (int k = i + 1; k < j; k++) {
                int x = sortedPoints[k][0], y = sortedPoints[k][1];
                
                if (y >= bobY && y <= aliceY) {
                    valid = 0;
                    break;
                }
            }
            
            if (valid) count++;
        }
    }
    
    free(sortedPoints);
    return count;
}
