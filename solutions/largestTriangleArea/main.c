double largestTriangleArea(int** points, int pointsSize, int* pointsColSize) {
    double res = 0.0;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            for (int k = j + 1; k < pointsSize; k++) {
                double area = 0.5 * fabs(points[i][0] * (points[j][1] - points[k][1]) + points[j][0] * (points[k][1] - points[i][1]) + points[k][0] * (points[i][1] - points[j][1]));
                if (area > res) {
                    res = area;
                }
            }
        }
    }   
    return res;
}