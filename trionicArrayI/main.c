bool isTrionic(int* nums, int numsSize) {
    int n = numsSize;
    
    if (n < 3) return false;
    
    int i = 1;
    int prev = nums[0];
    
    while (i < n && prev < nums[i]) {
        prev = nums[i];
        i++;
    }
    int p = i - 1;
    
    if (p == 0) return false;
    
    while (i < n && prev > nums[i]) {
        prev = nums[i];
        i++;
    }
    int q = i - 1;
    
    if (q == p) return false;
    
    while (i < n && prev < nums[i]) {
        prev = nums[i];
        i++;
    }
    
    return (i == n) && (i - 1 != q);
}