#include <string.h>

int minimumDistance(int* nums, int numsSize) {
  int capacity = 10000;
  int* keys = malloc(capacity * sizeof(int));
  int* last_pos = malloc(capacity * sizeof(int));
  int* second_last_pos = malloc(capacity * sizeof(int));
  int count = 0;

  int min_distance = INT_MAX;

  for (int i = 0; i < numsSize; i++) {
      int val = nums[i];
      int idx = -1;

      // Busca o valor no hash map
      for (int j = 0; j < count; j++) {
          if (keys[j] == val) {
              idx = j;
              break;
          }
      }

      if (idx == -1) {
          if (count < capacity) {
              keys[count] = val;
              last_pos[count] = i;
              second_last_pos[count] = -1;
              count++;
          }
      } else {
          // Valor já existe
          if (second_last_pos[idx] != -1) {
              int distance = 2 * (i - second_last_pos[idx]);
              if (distance < min_distance) {
                  min_distance = distance;
              }
          }
          second_last_pos[idx] = last_pos[idx];
          last_pos[idx] = i;
      }
  }

  free(keys);
  free(last_pos);
  free(second_last_pos);

  return (min_distance == INT_MAX) ? -1 : min_distance;
}