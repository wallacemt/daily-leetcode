#include <stdio.h>
#include <stdlib.h>

long long largestSquareArea(int** bottomLeft, int bottomLeftSize, int* bottomLeftColSize, int** topRight, int topRightSize, int* topRightColSize) {
    (void)bottomLeftColSize;
    (void)topRightColSize;

    int n = bottomLeftSize;
    long long maxSquare = 0;

    for (int i = 0; i < n - 1; i++) {
        long long c = topRight[i][0], d = topRight[i][1];
        long long a = bottomLeft[i][0], b = bottomLeft[i][1];

        for (int j = i + 1; j < n; j++) {
            long long width = ((c < topRight[j][0]) ? c : topRight[j][0]) - ((a > bottomLeft[j][0]) ? a : bottomLeft[j][0]);
            
            if (width > maxSquare) {
                long long height = ((d < topRight[j][1]) ? d : topRight[j][1]) - ((b > bottomLeft[j][1]) ? b : bottomLeft[j][1]);
                
                if (height > 0) {
                    long long square = (width < height) ? width : height;
                    if (square > maxSquare)
                        maxSquare = square;
                }
            }
        }
    }

    return maxSquare * maxSquare;
}