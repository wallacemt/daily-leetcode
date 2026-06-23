#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

static int cmp(const void* a, const void* b) {
  return *(int*)a - *(int*)b;
}

typedef struct {
  int* keys;
  char* used;
  int size;
} HashSet;

HashSet* createSet(int cap) {
  HashSet* set = (HashSet*)malloc(sizeof(HashSet));
  set->size = cap;
  set->keys = (int*)malloc(sizeof(int) * cap);
  set->used = (char*)calloc(cap, 1);
  return set;
}

void freeSet(HashSet* set) {
  free(set->keys);
  free(set->used);
  free(set);
}

static inline int hashInt(int x, int size) {
  return ((long long)x * 2654435761ULL) % size;
}

void setAdd(HashSet* set, int key) {
  int idx = hashInt(key, set->size);
  while (set->used[idx]) {
    if (set->keys[idx] == key) return;
    idx = (idx + 1) % set->size;
  }
  set->used[idx] = 1;
  set->keys[idx] = key;
}

bool setContains(HashSet* set, int key) {
  int idx = hashInt(key, set->size);
  while (set->used[idx]) {
    if (set->keys[idx] == key) return true;
    idx = (idx + 1) % set->size;
  }
  return false;
}

int maximizeSquareArea(int height, int width, int* hFences, int hSize,
                       int* vFences, int vSize) {
  const long long MOD = 1000000007LL;

  int H = hSize + 2, V = vSize + 2;
  int* h = (int*)malloc(sizeof(int) * H);
  int* v = (int*)malloc(sizeof(int) * V);

  h[0] = 1;
  memcpy(h + 1, hFences, sizeof(int) * hSize);
  h[H - 1] = height;

  v[0] = 1;
  memcpy(v + 1, vFences, sizeof(int) * vSize);
  v[V - 1] = width;

  qsort(h, H, sizeof(int), cmp);
  qsort(v, V, sizeof(int), cmp);

  int maxPairs = (H * (H - 1)) / 2;
  HashSet* set = createSet(maxPairs * 2 + 1);

  for (int i = 0; i < H - 1; i++) {
    for (int j = i + 1; j < H; j++) {
      setAdd(set, h[j] - h[i]);
    }
  }

  long long best = 0;

  for (int i = 0; i < V - 1; i++) {
    for (int j = i + 1; j < V; j++) {
      int diff = v[j] - v[i];
      if (diff > best && setContains(set, diff)) {
        best = diff;
      }
    }
  }

  freeSet(set);
  free(h);
  free(v);

  if (best == 0) return -1;

  long long ans = (best * best) % MOD;
  return (int)ans;
}