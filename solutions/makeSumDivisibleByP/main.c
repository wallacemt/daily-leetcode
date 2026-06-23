#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>

/* LeetCode 1590 style: find shortest subarray removal so sum % p == 0.
    Performance-focused C implementation (open addressing hash). */

static inline int hash_index(uint32_t k, int cap) {
     /* Knuth multiplicative constant for 32-bit, cap is power of two */
     return (int)((k * 2654435761u) & (uint32_t)(cap - 1));
}

int minSubarray(int* nums, int numsSize, int p) {
     if (numsSize == 0) return -1;

     /* compute total modulo p while keeping values reduced */
     int total = 0;
     for (int i = 0; i < numsSize; ++i) {
          int r = nums[i] % p;
          if (r < 0) r += p;
          total += r;
          if (total >= p) total -= p;
     }
     int target = total % p;
     if (target == 0) return 0;

     /* prepare hash table (open addressing). choose capacity ~2*numsSize */
     int need_slots = numsSize * 2 + 4;
     int cap = 1;
     while (cap < need_slots) cap <<= 1;

     int32_t *keys = malloc(sizeof(int32_t) * cap);
     int *vals = malloc(sizeof(int) * cap);
     if (!keys || !vals) {
          free(keys); free(vals);
          return -1;
     }

     /* sentinel for empty slot */
     for (int i = 0; i < cap; ++i) keys[i] = INT_MIN;

     /* store prefix 0 at index -1 */
     int k0 = 0;
     int idx = hash_index((uint32_t)k0, cap);
     while (keys[idx] != INT_MIN && keys[idx] != k0) idx = (idx + 1) & (cap - 1);
     keys[idx] = k0;
     vals[idx] = -1;

     int ans = numsSize + 1;
     int prefix = 0;
     for (int i = 0; i < numsSize; ++i) {
          int r = nums[i] % p;
          if (r < 0) r += p;
          prefix += r;
          if (prefix >= p) prefix -= p;

          int need = prefix - target;
          if (need < 0) need += p;

          /* lookup need */
          int j = hash_index((uint32_t)need, cap);
          while (keys[j] != INT_MIN) {
                if (keys[j] == need) {
                     int prev = vals[j];
                     int len = i - prev;
                     if (len < ans) ans = len;
                     break;
                }
                j = (j + 1) & (cap - 1);
          }

          /* store/update current prefix -> i (overwrite to keep most recent) */
          int t = hash_index((uint32_t)prefix, cap);
          while (keys[t] != INT_MIN && keys[t] != prefix) t = (t + 1) & (cap - 1);
          keys[t] = prefix;
          vals[t] = i;
     }

     free(keys);
     free(vals);

     if (ans >= numsSize) return -1;
     return ans;
}