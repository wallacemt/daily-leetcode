#include <limits.h>
#include <stdlib.h>

int minVal(int a, int b) {
    return (a < b) ? a : b;
}
typedef struct {
    int val;
    int index;
} Node;

int compare(const void* a, const void* b) {
    Node* nodeA = (Node*)a;
    Node* nodeB = (Node*)b;
    if (nodeA->val != nodeB->val) return nodeA->val - nodeB->val;
    return nodeA->index - nodeB->index;
}

int minimumDistance(int* nums, int numsSize) {
    if (numsSize <= 2) return -1;
    Node* nodes = malloc(numsSize * sizeof(Node));
    for (int i = 0; i < numsSize; i++) {
        nodes[i].val = nums[i];
        nodes[i].index = i;
    }
    qsort(nodes, numsSize, sizeof(Node), compare);

    int ans = INT_MAX;

    for (int i = 0; i + 2 < numsSize; i++) {
        if (nodes[i].val == nodes[i + 2].val) {
            int dist = 2 * (nodes[i + 2].index - nodes[i].index);
            ans = minVal(ans, dist);
        }
    }

    free(nodes);
    return (ans == INT_MAX) ? -1 : ans;
}