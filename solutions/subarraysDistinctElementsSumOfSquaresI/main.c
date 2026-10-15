#include <limits.h>
#define MAX_NUM 100
int sumCounts(int* nums, int numsSize) {
    int sum = 0;
    int freq[MAX_NUM + 1] = {0};  
 
    for (int i = 0; i < numsSize; ++i) {
        // Reseta o vetor de frequência
        memset(freq, 0, sizeof(freq));
        int uniqueCnt = 0;

        // 2. Estende o subarray para a direita
        for (int j = i; j < numsSize; ++j) {
            int num = nums[j];
 
            if (freq[num] == 0) {
                uniqueCnt++;
            }
            freq[num]++;
 
            sum += uniqueCnt * uniqueCnt;
        }
    }

    return sum;
}