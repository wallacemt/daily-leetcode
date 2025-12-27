int cmp(const void* a, const void* b) {
    int* x = *(int**)a;
    int* y = *(int**)b;
    return x[0] - y[0];
}

int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    qsort(meetings, meetingsSize, sizeof(int*), cmp);

    int* count = calloc(n, sizeof(int));
    long* timer = calloc(n, sizeof(long));

    int intr = 0;

    while (intr < meetingsSize) {
        int start = meetings[intr][0];
        int end = meetings[intr][1];
        long dur = end - start;

        int room = -1;
        long earliest = LONG_MAX;
        int earliestRoom = -1;

        for (int i = 0; i < n; i++) {
            if (timer[i] < earliest) {
                earliest = timer[i];
                earliestRoom = i;
            }
            if (timer[i] <= start) {
                room = i;
                break;
            }
        }

        if (room != -1) {
            timer[room] = end;
            count[room]++;
        } else {
            timer[earliestRoom] += dur;
            count[earliestRoom]++;
        }

        intr++;
    }

    int max = 0, idx = 0;
    for (int i = 0; i < n; i++) {
        if (count[i] > max) {
            max = count[i];
            idx = i;
        }
    }

    free(count);
    free(timer);
    return idx;
}