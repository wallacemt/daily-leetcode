
int search(int* nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (nums[mid] == target) {
            return mid;
        }
        if (nums[mid] >= nums[left]) {
            if (target >= nums[left] && target < nums[mid]) {
                // Target está na esquerda ordenada
                right = mid - 1;
            } else {
                // Target está na direita
                left = mid + 1;
            }
        } else {
            if (target > nums[mid] && target <= nums[right]) {
                // Target está na direita ordenada
                left = mid + 1;
            } else {
                // Target está na esquerda
                right = mid - 1;
            }
        }
    }
    
    return -1;
}