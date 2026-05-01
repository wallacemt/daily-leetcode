#define MAXN 200001

int max(int a, int b) {
    return a > b ? a : b;
}

int maxRotateFunction(int* nums, int n) {
    int total_sum = 0;
    int current_value = 0;
    
    for (int i = 0; i < n; i++) {
        total_sum += nums[i];
        current_value += i * nums[i];
    }
    
    int ans = current_value;
    
    for (int i = 1; i < n; i++) {
        current_value = current_value + total_sum - n * nums[n - i];
        ans = max(ans, current_value);
    }
    
    return ans;
}