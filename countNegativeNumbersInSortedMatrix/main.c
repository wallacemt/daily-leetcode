int countNegatives(int** grid, int gridSize, int* gridColSize) {
    int count = 0;
    
    for(int i = 0; i < gridSize; i++) {
        int cols = gridColSize[i];
        
        int left = 0, right = cols - 1;
        int firstNegativeIdx = cols; 
        
        while(left <= right) {
            int mid = left + (right - left) / 2;
            if(grid[i][mid] < 0) {
                firstNegativeIdx = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        count += cols - firstNegativeIdx;
    }
    
    return count;
}