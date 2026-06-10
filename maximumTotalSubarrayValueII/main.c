typedef struct { int val, l, r; } Node;

typedef struct {
    Node* data;
    int size;
} MaxHeap;

void swap(Node* a, Node* b) { Node temp = *a; *a = *b; *b = temp; }

void push(MaxHeap* h, Node node) {
    h->data[++h->size] = node;
    int i = h->size;
    while (i > 1 && h->data[i].val > h->data[i / 2].val) {
        swap(&h->data[i], &h->data[i / 2]);
        i /= 2;
    }
}

Node pop(MaxHeap* h) {
    Node top = h->data[1];
    h->data[1] = h->data[h->size--];
    int i = 1;
    while (2 * i <= h->size) {
        int j = 2 * i;
        if (j + 1 <= h->size && h->data[j + 1].val > h->data[j].val) j++;
        if (h->data[i].val >= h->data[j].val) break;
        swap(&h->data[i], &h->data[j]);
        i = j;
    }
    return top;
}

int get_max(int* seg, int l, int r, int size) {
    int mx = 0;
    for (l += size, r += size; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) { if (seg[l] > mx) mx = seg[l]; l++; }
        if (!(r & 1)) { if (seg[r] > mx) mx = seg[r]; r--; }
    }
    return mx;
}

int get_min(int* seg, int l, int r, int size) {
    int mn = 1e9;
    for (l += size, r += size; l <= r; l >>= 1, r >>= 1) {
        if (l & 1) { if (seg[l] < mn) mn = seg[l]; l++; }
        if (!(r & 1)) { if (seg[r] < mn) mn = seg[r]; r--; }
    }
    return mn;
}

long long maxTotalValue(int* nums, int n, int k) {
    int size = 1; while (size < n) size *= 2;
    int* seg_max = calloc(2 * size, sizeof(int));
    int* seg_min = malloc(2 * size * sizeof(int));
    for (int i = 0; i < 2 * size; i++) seg_min[i] = 1e9;

    for (int i = 0; i < n; i++) seg_max[size + i] = seg_min[size + i] = nums[i];
    for (int i = size - 1; i > 0; i--) {
        seg_max[i] = (seg_max[2 * i] > seg_max[2 * i + 1]) ? seg_max[2 * i] : seg_max[2 * i + 1];
        seg_min[i] = (seg_min[2 * i] < seg_min[2 * i + 1]) ? seg_min[2 * i] : seg_min[2 * i + 1];
    }

    MaxHeap h;
    h.data = malloc((n + k + 1) * sizeof(Node));
    h.size = 0;

    for (int i = 0; i < n; i++) {
        int val = get_max(seg_max, i, n - 1, size) - get_min(seg_min, i, n - 1, size);
        push(&h, (Node){val, i, n - 1});
    }

    long long ans = 0;
    for (int i = 0; i < k; i++) {
        Node top = pop(&h);
        ans += top.val;
        if (top.r > top.l) {
            int val = get_max(seg_max, top.l, top.r - 1, size) - get_min(seg_min, top.l, top.r - 1, size);
            push(&h, (Node){val, top.l, top.r - 1});
        }
    }
    return ans;
}