#include <limits.h>

int addition(int nbr) {
    int total = 0;

    while (nbr) {
        total += nbr % 10;
        nbr /= 10;
    }
    return (total);
}

int minElement(int* nums, int numsSize) {
    int min;
    int i;

    if (numsSize <= 0)
        return (-1);

    min = addition(nums[0]);

    for (i = 1; i < numsSize; i++) {
        int total = addition(nums[i]);
        if (total < min)
            min = total;
    }
    return (min);
}