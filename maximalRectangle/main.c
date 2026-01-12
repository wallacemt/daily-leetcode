typedef unsigned int UI4;

#define MASTER_MAX(value1, value2) (((value1) > (value2)) ? (value1) : (value2))
#define MASTER_IMAX(value1, value2) (value1) = MASTER_MAX(value1, value2)

UI4 MASTER_Algolib_LargestRectangleArea(const UI4 * const heights, const UI4 heightsSize) {
    UI4 mstack[201];
    UI4 maxArea = 0;
    UI4 mstack_pos = 0;
    
    for (UI4 index = 0; index < heightsSize; index++) {
        UI4 curHeight = heights[index];
        
        while (mstack_pos > 0 && heights[mstack[mstack_pos - 1]] > curHeight) {
            mstack_pos--;
            UI4 popHeight = heights[mstack[mstack_pos]];
            UI4 width = (mstack_pos == 0) ? index : (index - mstack[mstack_pos - 1] - 1);
            MASTER_IMAX(maxArea, width * popHeight);
        }
        
        mstack[mstack_pos++] = index;
    }
    
    while (mstack_pos > 0) {
        mstack_pos--;
        UI4 popHeight = heights[mstack[mstack_pos]];
        UI4 width = (mstack_pos == 0) ? heightsSize : (heightsSize - mstack[mstack_pos - 1] - 1);
        MASTER_IMAX(maxArea, width * popHeight);
    }
    
    return maxArea;
}

UI4 maximalRectangle(char** matrix, const UI4 matrixSize, const UI4 * const matrixColSize) {
    const UI4 columns = matrixColSize[0];
    UI4 maxArea = 0;
    UI4 heights[201];
    
    memset(heights, 0, sizeof(heights));
    
    for (UI4 index = 0; index < matrixSize; index++) {
        for (UI4 jndex = 0; jndex < columns; jndex++) {
            heights[jndex] = (matrix[index][jndex] == '1') ? (heights[jndex] + 1) : 0;
        }
        
        UI4 newArea = MASTER_Algolib_LargestRectangleArea(heights, columns);
        MASTER_IMAX(maxArea, newArea);
    }
    
    return maxArea;
}