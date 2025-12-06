#pragma GCC optimize("O3,unroll-loops,inline")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
static const int mod = 1e9 + 7;
static int qMax[50000], qMin[50000];
static int frontX, backX, frontN, backN;

static inline int countPartitions(int* restrict nums, int n, int k) {
    frontX = frontN = 0;
    backX = backN = -1;

    long long cnt = 0;
    int* restrict sum = (int*)alloca((n + 2) * sizeof(int));
    sum[0] = 0;
    sum[1] = 1;

    for (int l = 0, r = 0; r < n; r++) {
        const int x = nums[r];

        while (backX >= frontX && qMax[backX] < x) backX--;
        qMax[++backX] = x;

         while (backN >= frontN && qMin[backN] > x) backN--;
        qMin[++backN] = x;

        int diff = qMax[frontX] - qMin[frontN];
        while (diff > k) {
            const int y = nums[l];
            frontX += (qMax[frontX] == y);
            frontN += (qMin[frontN] == y);
            l++;
            diff = qMax[frontX] - qMin[frontN];
        }

        cnt = sum[r + 1] - sum[l];
        if (cnt < 0) cnt += mod;
        sum[r + 2] = sum[r + 1] + cnt;
        if (sum[r + 2] >= mod) sum[r + 2] -= mod;
    }
    return cnt;
}