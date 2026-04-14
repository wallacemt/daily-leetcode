#define INF 1e18

typedef struct {
    int idx;
    long long val;
} Pair;

int cmp_int(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int cmp_factory(const void* a, const void* b) {
    return (*(int**)a)[0] - (*(int**)b)[0];
}

long long minimumTotalDistance(int* robot, int robotSize, int** factory, int factorySize, int* factoryColSize) {
    qsort(robot, robotSize, sizeof(int), cmp_int);
    qsort(factory, factorySize, sizeof(int*), cmp_factory);

    long long** dp = malloc((robotSize + 1) * sizeof(long long*));
    for (int i = 0; i <= robotSize; i++) {
        dp[i] = calloc(factorySize + 1, sizeof(long long));
    }

    for (int i = 0; i < robotSize; i++) {
        dp[i][factorySize] = INF;
    }

    for (int j = factorySize - 1; j >= 0; j--) {
        long long prefix = 0;
        Pair dq[robotSize + 1]; // Buffer fixo
        int front = 0, back = 0;
        dq[back++] = (Pair){robotSize, 0};

        for (int i = robotSize - 1; i >= 0; i--) {
            prefix += robot[i] < factory[j][0] ? factory[j][0] - robot[i] : robot[i] - factory[j][0];

            while (front < back && dq[front].idx > i + factory[j][1]) {
                front++;
            }

            long long val = dp[i][j + 1] - prefix;

            while (front < back && dq[back - 1].val >= val) {
                back--;
            }

            dq[back++] = (Pair){i, val};

            dp[i][j] = dq[front].val + prefix;
        }
    }

    long long ans = dp[0][0];

    for (int i = 0; i <= robotSize; i++) 
        free(dp[i]);
    free(dp);

    return ans;
}
