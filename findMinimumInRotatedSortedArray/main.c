int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    
    while (right > 0 && nums[right] == nums[right - 1]) {
        right--;
    }
    
    while (left < right) {
        
        int mid = left + (right - left) / 2;
        
        if (nums[mid] > nums[right]) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return nums[left];
}