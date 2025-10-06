#include <stdbool.h>
#include <string.h>

bool canReach(int** grid, int n, int maxTime) {
    if (grid[0][0] > maxTime) return false;
    bool visited[n][n];
    memset(visited, false, sizeof(visited));
    int stack[n * n][2];
    int top = 0;
    
    stack[top][0] = 0;
    stack[top][1] = 0;
    top++;
    visited[0][0] = true;
    
    int dirs[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};
    
    while (top > 0) {
        top--;
        int x = stack[top][0];
        int y = stack[top][1];
        
        if (x == n-1 && y == n-1) return true;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            
            if (nx >= 0 && nx < n && ny >= 0 && ny < n && 
                !visited[nx][ny] && grid[nx][ny] <= maxTime) {
                visited[nx][ny] = true;
                stack[top][0] = nx;
                stack[top][1] = ny;
                top++;
            }
        }
    }
    return false;
}

int swimInWater(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    int left = grid[0][0];
    int right = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] > right) right = grid[i][j];
        }
    }
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (canReach(grid, n, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}