/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
typedef long long ll;

typedef struct {
    ll time;
    int weight;
    int index;
} Node;

typedef struct {
    Node* data;
    int size;
    int capacity;
    int busy;
} Heap;

static int lessNode(Node a, Node b, int busy) {
    if (busy && a.time != b.time)
        return a.time < b.time;

    if (a.weight != b.weight)
        return a.weight < b.weight;

    return a.index < b.index;
}

static Heap* createHeap(int capacity, int busy) {
    Heap* h = malloc(sizeof(Heap));
    h->data = malloc(capacity * sizeof(Node));
    h->size = 0;
    h->capacity = capacity;
    h->busy = busy;
    return h;
}

static void heapPush(Heap* h, Node value) {
    int i = h->size++;
    h->data[i] = value;

    while (i > 0) {
        int p = (i - 1) / 2;
        if (!lessNode(h->data[i], h->data[p], h->busy))
            break;

        Node tmp = h->data[i];
        h->data[i] = h->data[p];
        h->data[p] = tmp;
        i = p;
    }
}

static Node heapPop(Heap* h) {
    Node result = h->data[0];
    h->size--;

    if (h->size == 0)
        return result;

    h->data[0] = h->data[h->size];

    int i = 0;
    while (1) {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int best = i;

        if (l < h->size &&
            lessNode(h->data[l], h->data[best], h->busy))
            best = l;

        if (r < h->size &&
            lessNode(h->data[r], h->data[best], h->busy))
            best = r;

        if (best == i)
            break;

        Node tmp = h->data[i];
        h->data[i] = h->data[best];
        h->data[best] = tmp;
        i = best;
    }

    return result;
}

int* assignTasks(int* servers, int serversSize, int* tasks, int tasksSize, int* returnSize) {
    int n = serversSize, m = tasksSize;
    *returnSize = m;

    int* ans = malloc(m * sizeof(int));

    Heap* heapsmol = createHeap(n, 0);
    Heap* heaplarge = createHeap(n, 1);

    for (int i = 0; i < n; i++) {
        heapPush(heapsmol, (Node){0, servers[i], i});
    }

    for (int i = 0; i < m; i++) {
        while (heaplarge->size > 0 &&
               heaplarge->data[0].time <= i) {
            Node node = heapPop(heaplarge);
            heapPush(heapsmol, node);
        }

        if (heapsmol->size > 0) {
            Node node = heapPop(heapsmol);
            ans[i] = node.index;
            node.time = (ll)i + tasks[i];
            heapPush(heaplarge, node);
        } else {
            Node node = heapPop(heaplarge);
            ans[i] = node.index;
            node.time += tasks[i];
            heapPush(heaplarge, node);
        }
    }

    free(heapsmol->data);
    free(heaplarge->data);
    free(heapsmol);
    free(heaplarge);

    return ans;
}