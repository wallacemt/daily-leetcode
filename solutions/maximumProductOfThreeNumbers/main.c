int maximumProduct(int* nums, int numsSize) {
    long long max1 = LLONG_MIN, max2 = LLONG_MIN, max3 = LLONG_MIN;
    long long min1 = LLONG_MAX, min2 = LLONG_MAX;

    for (int i = 0; i < numsSize; i++) {
        long long num = nums[i];  
 
        if (num > max1) {
            max3 = max2;
            max2 = max1;
            max1 = num;
        } else if (num > max2) {
            max3 = max2;
            max2 = num;
        } else if (num > max3) {
            max3 = num;
        }
 
        if (num < min1) {
            min2 = min1;
            min1 = num;
        } else if (num < min2) {
            min2 = num;
        }
    }

    long long product1 = max1 * max2 * max3;
    long long product2 = max1 * min1 * min2;

    return product1 > product2 ? product1 : product2;
}