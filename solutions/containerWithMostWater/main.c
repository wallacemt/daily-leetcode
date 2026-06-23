int maxArea(int* height, int heightSize) {
    if (!height || heightSize < 2) {
        return 0;
    }
    int left = 0;
    int right = heightSize - 1;
    int max_area = 0;
    
    while (left < right) {
        int min_height = (height[left] < height[right]) ? height[left] : height[right];
        int current_area = min_height * (right - left);
        if (current_area > max_area) {
            max_area = current_area;
        }
        if (height[left] < height[right]) {
            left++;
        } else {
            right--;
        }
    }
    return max_area;
}