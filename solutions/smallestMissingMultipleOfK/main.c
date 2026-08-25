#include <stdbool.h>
#include <stdint.h>

#define MAX_NUM 100
#define BITSET_SIZE ((MAX_NUM / 64) + 1)

int missingMultiple(const int* nums, int numsSize, int div) {
    if (div <= 0 || nums == NULL || numsSize < 0) {
        return -1;
    }

    uint64_t presentNums[BITSET_SIZE] = {0};

    for (int i = 0; i < numsSize; ++i) {
        const int value = nums[i];

        if (value >= 0 && value <= MAX_NUM) {
            const int word = value / 64;
            const int bit = value % 64;

            presentNums[word] |= (UINT64_C(1) << bit);
        }
    }

    if (div > MAX_NUM) {
        return div;
    }

    for (int multiple = div; multiple <= MAX_NUM; multiple += div) {
        const int word = multiple / 64;
        const int bit = multiple % 64;

        if ((presentNums[word] & (UINT64_C(1) << bit)) == 0) {
            return multiple;
        }
    }

    return MAX_NUM - (MAX_NUM % div) + div;
}
