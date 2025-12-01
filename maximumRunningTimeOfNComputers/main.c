long long maxRunTime(int n, int* batteries, int batteriesSize) {
    long long sum = 0;
    for (int i = 0; i < batteriesSize; i++) {
        sum += batteries[i];
    }

    long long low = 1, high = sum / n;
    long long ans = 0;

    while (low <= high) {
        long long mid = low + (high - low) / 2;
        long long totalPower = 0;

        for (int i = 0; i < batteriesSize; i++) {
            if (batteries[i] < mid) {
                totalPower += batteries[i];
            } else {
                totalPower += mid;
            }
        }

        if (totalPower >= (long long)n * mid) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return ans;
}
