#pragma GCC optimize("O3,unroll-loops,inline")
#define SZ 100001
int xMin[SZ], xMax[SZ], yMin[SZ], yMax[SZ];

static int countCoveredBuildings(int n, int** buildings, int bz, int* buildingsColSize) {
    int M = 0, N = 0;
    
    for(int i = 0; i < bz; i++){
        const int x = buildings[i][0];
        const int y = buildings[i][1];
        M = (x > M) ? x : M;
        N = (y > N) ? y : N;
    }
    
    for(int i = 0; i <= N; i++) {
        xMin[i] = INT_MAX;
        xMax[i] = 0;
    }
    for(int i = 0; i <= M; i++) {
        yMin[i] = INT_MAX;
        yMax[i] = 0;
    }

    for(int i = 0; i < bz; i++){
        const int x = buildings[i][0];
        const int y = buildings[i][1];
        xMin[y] = (x < xMin[y]) ? x : xMin[y];
        xMax[y] = (x > xMax[y]) ? x : xMax[y];
        yMin[x] = (y < yMin[x]) ? y : yMin[x];
        yMax[x] = (y > yMax[x]) ? y : yMax[x];
    }

    int cnt = 0;
    for(int i = 0; i < bz; i++){
        const int x = buildings[i][0];
        const int y = buildings[i][1];
        cnt += (xMin[y] < x && x < xMax[y] && yMin[x] < y && y < yMax[x]);
    }
    return cnt;
}