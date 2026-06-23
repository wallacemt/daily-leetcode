#include <stdlib.h>
#include <limits.h>

typedef struct {
    long long sum;
    int index;
} HeapNode;

typedef struct {
    HeapNode* data;
    int size;
    int cap;
} MinHeap;

MinHeap* createHeap(int cap) {
    MinHeap* h = (MinHeap*)malloc(sizeof(MinHeap));
    h -> data = (HeapNode*)malloc(sizeof(HeapNode) * cap);
    h -> size = 0;
    h -> cap = cap;
    return h;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

int isGreater(HeapNode a, HeapNode b) {
    if (a.sum != b.sum) {
        return a.sum > b.sum;
    }
    return a.index > b.index;
}

void pushHeap(MinHeap* h, long long sum, int index) {
    if (h -> size == h -> cap) {
        return;
    }
    int i = h -> size++;
    h -> data[i].sum = sum;
    h -> data[i].index = index;
    
    while (i > 0) {
        int p = (i - 1) / 2;
        if (isGreater(h -> data[p], h -> data[i])) {
            swap(&h -> data[p], &h -> data[i]);
            i = p;
        } else {
            break;
        }
    }
}

HeapNode popHeap(MinHeap* h) {
    HeapNode ret = h -> data[0];
    h -> data[0] = h -> data[--h -> size];
    int i = 0;
    
    while (2 * i + 1 < h -> size) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = left;
        
        if (right < h -> size && isGreater(h -> data[left], h -> data[right])) {
            smallest = right;
        }
        
        if (isGreater(h -> data[i], h -> data[smallest])) {
            swap(&h -> data[i], &h -> data[smallest]);
            i = smallest;
        } else {
            break;
        }
    }
    return ret;
}

long long getVal(long long* l, int i, int n) {
    if (i < 0 || i >= n) {
        return LLONG_MAX;
    }
    return l[i];
}

int minimumPairRemoval(int* nums, int numsSize) {
    int n = numsSize;
    long long* l = (long long*)malloc(sizeof(long long) * n);
    for(int i = 0; i < n; i++) {
        l[i] = nums[i];
    }
    
    int* le = (int*)malloc(sizeof(int) * n);
    int* ri = (int*)malloc(sizeof(int) * n);
    
    for(int i = 0; i < n; i++) {
        le[i] = i - 1;
        ri[i] = i + 1;
    }
    
    MinHeap* h = createHeap(n * 4 + 1000); 
    
    int sortedPairs = 0;
    for(int i = 0; i < n; i++) {
        long long curr = l[i];
        long long next = getVal(l, i + 1, n);
        if (curr <= next) {
            sortedPairs++;
        }
        
        if (i < n - 1) {
            pushHeap(h, l[i] + l[i + 1], i);
        }
    }
    
    int rest = n - sortedPairs;
    int ans = 0;
    
    while (rest > 0 && h -> size > 0) {
        HeapNode top = popHeap(h);
        long long v = top.sum;
        int i = top.index;
        int r = ri[i];
        
        if (r >= n || le[r] != i || l[i] + l[r] != v) {
            continue;
        }
        
        int rr = (r < n) ? ri[r] : n;
        
        if (getVal(l, le[i], n) <= l[i]) {
            rest++;
        }
        if (l[i] <= l[r]) {
            rest++;
        }
        if (l[r] <= getVal(l, rr, n)) {
            rest++;
        }
        
        if (rr < n) {
            le[rr] = i;
        }        
        ri[i] = rr;
        l[i] = v; 
        
        rest--; 
        if (getVal(l, le[i], n) <= l[i]) {
            rest--;
        }
        if (l[i] <= getVal(l, rr, n)) {
            rest--;
        }
        
        if (le[i] != -1) {
            pushHeap(h, l[le[i]] + l[i], le[i]);
        }
        if (rr < n) {
            pushHeap(h, l[i] + l[rr], i);
        }
        
        ans++;
    }
    
    free(l);
    free(le);
    free(ri);
    free(h -> data);
    free(h);
    
    return ans;
}

