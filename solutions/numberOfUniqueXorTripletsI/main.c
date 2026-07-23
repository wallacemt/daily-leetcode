int uniqueXorTriplets(int* nums, int numsSize) {
    int n = numsSize;
    if (n < 3) return n;
 
    int nearest = 31 - __builtin_clz(n);
    
    return 1 << (nearest + 1);
}