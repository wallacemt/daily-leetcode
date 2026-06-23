#pragma GCC optimize("O3,unroll-loops")

int minTimeToVisitAllPoints(int** points, int n, int* pointsColSize) {
    int ans = 0;
    for(int i = 0; i < n - 1; i++) {
        int dx = points[i+1][0] - points[i][0];
        int dy = points[i+1][1] - points[i][1];
        
        dx = (dx ^ (dx >> 31)) - (dx >> 31);
        dy = (dy ^ (dy >> 31)) - (dy >> 31);
        
        ans += (dx > dy) ? dx : dy;
    }
    return ans;
}
