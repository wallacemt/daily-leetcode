int find(int x, int* p) {
    if (p[x] != x) p[x] = find(p[x], p);
    return p[x];
}

void unite(int a, int b, int* p, int* rank) {
    int pa = find(a, p), pb = find(b, p);
    if (pa != pb) {
        if (rank[pa] < rank[pb]) {
            p[pa] = pb;
        } else if (rank[pa] > rank[pb]) {
            p[pb] = pa;
        } else {
            p[pb] = pa;
            rank[pa]++;
        }
    }
}

int cmp(const void* a, const void* b) {
    return (*(int**)a)[2] - (*(int**)b)[2];
}

int* findAllPeople(int n, int** meetings, int meetingsSize, int* meetingsColSize,
                   int firstPerson, int* returnSize) {

    qsort(meetings, meetingsSize, sizeof(int*), cmp);

    int* parent = malloc(n * sizeof(int));
    int* rank = calloc(n, sizeof(int));
    int* know = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) parent[i] = i;

    know[0] = know[firstPerson] = 1;
    unite(0, firstPerson, parent, rank);

    int* temp = malloc(2 * meetingsSize * sizeof(int));
    int tempSize = 0;

    int i = 0;
    while (i < meetingsSize) {
        int t = meetings[i][2];
        tempSize = 0;

        int j = i;
        while (j < meetingsSize && meetings[j][2] == t) {
            unite(meetings[j][0], meetings[j][1], parent, rank);
            temp[tempSize++] = meetings[j][0];
            temp[tempSize++] = meetings[j][1];
            j++;
        }

        for (int k = 0; k < tempSize; k++) {
            int person = temp[k];
            int root = find(person, parent);
            if (find(0, parent) == root) {
                know[person] = 1;
            }
        }

        for (int k = 0; k < tempSize; k++) {
            int person = temp[k];
            if (!know[person]) {
                parent[person] = person;
                rank[person] = 0;
            }
        }

        i = j;
    }

    free(temp);

    int* res = malloc(n * sizeof(int));
    *returnSize = 0;
    for (int i = 0; i < n; i++)
        if (know[i]) res[(*returnSize)++] = i;

    free(parent);
    free(rank);
    free(know);
    return res;
}