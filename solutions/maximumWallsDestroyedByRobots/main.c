#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    long long pos;
    int dist;
} Robot;

int compareRobots(const void* a, const void* b) {
    long long diff = ((Robot*)a)->pos - ((Robot*)b)->pos;
    if (diff < 0) return -1;
    if (diff > 0) return 1;
    return 0;
}

int compareInts(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

int count_walls(int* walls, int wallsSize, long long l, long long r) {
    if (l > r) 
    return 0;

    int low = 0, high = wallsSize;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (walls[mid] < l) low = mid + 1;
        else high = mid;
    }
    int it_l = low;

    low = 0; high = wallsSize;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (walls[mid] <= r) low = mid + 1;
        else high = mid;
    }
    int it_r = low;

    return it_r - it_l;
}

int maxWalls(int* robots, int robotsSize, int* distance, int distanceSize, int* walls, int wallsSize) {
    int n = robotsSize;
    if (n == 0) 
        return 0;

    qsort(walls, wallsSize, sizeof(int), compareInts);

    Robot* r_data = (Robot*)malloc(n * sizeof(Robot));
    for (int i = 0; i < n; i++) {
        r_data[i].pos = robots[i];
        r_data[i].dist = distance[i];
    }
    qsort(r_data, n, sizeof(Robot), compareRobots);

    int (*dp)[2] = malloc(n * sizeof(int[2]));

    long long INF = 4e18;
    long long pos0 = r_data[0].pos;
    int dist0 = r_data[0].dist;
    long long next_r = (n > 1) ? r_data[1].pos : INF;

    dp[0][0] = count_walls(walls, wallsSize, pos0 - dist0, pos0);
    dp[0][1] = count_walls(walls, wallsSize, pos0, MIN(pos0 + dist0, next_r - 1));

    for (int i = 1; i < n; i++) {
        long long cur_p = r_data[i].pos;
        int cur_d = r_data[i].dist;
        long long pre_p = r_data[i - 1].pos;
        int pre_d = r_data[i - 1].dist;
        next_r = (i + 1 < n) ? r_data[i + 1].pos : INF;

        int r_gain = count_walls(walls, wallsSize, cur_p, MIN(cur_p + cur_d, next_r - 1));
        dp[i][1] = MAX(dp[i - 1][0], dp[i - 1][1]) + r_gain;

        long long l_lim = MAX(cur_p - cur_d, pre_p + 1);
        int l_gain = count_walls(walls, wallsSize, l_lim, cur_p);

        int case_left = dp[i - 1][0] + l_gain;

        long long over_r = MIN(pre_p + pre_d, cur_p - 1);
        int overlap = count_walls(walls, wallsSize, l_lim, over_r);
        int case_right = dp[i - 1][1] + l_gain - overlap;

        dp[i][0] = MAX(case_left, case_right);
    }

    int result = MAX(dp[n - 1][0], dp[n - 1][1]);

    free(r_data);
    free(dp);
    return result;
}