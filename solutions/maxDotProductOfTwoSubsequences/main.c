static int cmp_int(const void *a, const void *b){
    int x = *(const int*)a, y = *(const int*)b;
    return (x > y) - (x < y);
}
static int arr_max(const int *a, int n){
    int mx = a[0];
    for (int i = 1; i < n; i++){
        if (a[i] > mx)
            mx = a[i];
    }
    return mx;
}
static int arr_min(const int *a, int n){
    int mn = a[0];
    for (int i = 1; i < n; i++){
        if ( a[i] < mn)
            mn = a[i];
    }
    return mn;
}
int maxDotProduct(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    if (nums1Size > 0 && nums2Size > 0 && nums1[0] > nums2[0]){
        int *tmpA = nums1; nums1 = nums2; nums2 = tmpA;
        int tmpN = nums1Size; nums1Size = nums2Size; nums2Size = tmpN;
    }
    int max1 = arr_max(nums1, nums1Size);
    int min2 = arr_min(nums2, nums2Size);
    if (max1 < 0 && min2 > 0)
        return max1 * min2;
    int *dp = (int*) calloc((size_t)nums2Size + 1, sizeof(int));
    for (int i = 0; i < nums1Size; i++){
        for (int j = nums2Size - 1; j >= 0; j--){
            int v = nums1[i] * nums2[j] + dp[j];
            if (v > dp[j + 1])
                dp[j + 1] = v;
        }
        for (int j = 0; j < nums2Size; j++){
            if (dp[j + 1] < dp[j])
                dp[j + 1] = dp[j];
        }
    }
    int ans = dp[nums2Size];
    free(dp);
    return ans;
}