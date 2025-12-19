int find(int x, int* p) {
    if (p[x] != x) p[x] = find(p[x], p);
    return p[x];
}

void unite(int a, int b, int* p) {
    int pa = find(a, p), pb = find(b, p);
    if (pa != pb) p[pb] = pa;
}

int cmp(const void* a, const void* b) {
    return (*(int**)a)[2] - (*(int**)b)[2];
}

int* findAllPeople(int n, int** meetings, int meetingsSize, int* meetingsColSize,
                   int firstPerson, int* returnSize) {

    qsort(meetings, meetingsSize, sizeof(int*), cmp);

    int* parent = malloc(n * sizeof(int));
    int* know = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    know[0] = know[firstPerson] = 1;

    for (int i = 0; i < meetingsSize; ) {
        int t = meetings[i][2];
        int tempSize = 0;
        int temp[200000];

        int j = i;
        while (j < meetingsSize && meetings[j][2] == t) {
            unite(meetings[j][0], meetings[j][1], parent);
            temp[tempSize++] = meetings[j][0];
            temp[tempSize++] = meetings[j][1];
            j++;
        }

        for (int k = 0; k < tempSize; k++)
            if (know[temp[k]])
                know[find(temp[k], parent)] = 1;

        for (int k = 0; k < tempSize; k++)
            know[temp[k]] |= know[find(temp[k], parent)];

        for (int k = 0; k < tempSize; k++)
            parent[temp[k]] = temp[k];

        i = j;
    }

    int* res = malloc(n * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < n; i++)
        if (know[i]) res[(*returnSize)++] = i;

    return res;
}