int rev(int n) {
    int a = 0;
    while(n > 0) {
        a = a * 10 + (n % 10);
        n /= 10;
    }
    return a;
}
#define MIN(a,b) (a < b ? a : b)
int minMirrorPairDistance(int* nums, int numsSize) {
    int* hash = (int*)malloc(1000000001 * sizeof(int));
    int ans = INT_MAX;
    for(int i = numsSize - 1; i >= 0; i--) {
        int r = rev(nums[i]);
        if(hash[r] > 0) ans = MIN(ans, hash[r] - i);
        hash[nums[i]] = i; 
    }
    free(hash);
    if(ans == INT_MAX) return -1;
    return ans;
}


