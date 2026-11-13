#include <stdlib.h>

typedef struct {
    int value;
    int count;
} Node;

/**
 * Conta subarrays que podem se tornar não decrescentes com custo <= k.
 * Abordagem: Janela deslizante da direita para a esquerda com Deque Monotônico.
 */
long long countNonDecreasingSubarrays(int* nums, int numsSize, int k) {
    if (numsSize == 0) return 0;

    int n = numsSize;
    int right = n - 1;
    long long total_cost = 0;
    long long res = 0;

    Node* q = (Node*)malloc((2 * n + 1) * sizeof(Node));
    if (!q) return 0;  

    int head = n;
    int tail = n;

    for (int left = n - 1; left >= 0; left--) {
        int x = nums[left];
        int c = 1;
 
        while (head < tail && q[head].value < x) {
            long long diff = (long long)x - q[head].value;
            total_cost += diff * q[head].count;
            c += q[head].count;
            head++;
        }
         
        q[--head] = (Node){x, c};
 
        while (total_cost > (long long)k) { 
            total_cost -= (long long)q[tail - 1].value - nums[right];
            
            if (q[tail - 1].count > 1) {
                q[tail - 1].count--;
            } else {
                tail--;
            }
            right--;
        }
 
        res += (long long)right - left + 1;
    }

    free(q);
    return res;
}