int uniqueXorTriplets(int* nums, int numsSize) {
    int m = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > m) {
            m = nums[i];
        }
    }

    int size = 1;

    while (size <= m) {
        size <<= 1;
    }

    bool* one = calloc(size, sizeof(bool));
    bool* two = calloc(size, sizeof(bool));
    bool* three = calloc(size, sizeof(bool));

    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];
        one[x] = true;

        for (int y = 0; y < size; y++) {
            if (one[y]) {
                two[y ^ x] = true;
            }
        }
    }

    for (int i = 0; i < numsSize; i++) {
        int x = nums[i];

        for (int y = 0; y < size; y++) {
            if (two[y]) {
                three[y ^ x] = true;
            }
        }
    }

    int result = 0;

    for (int i = 0; i < size; i++) {
        result += three[i];
    }

    free(one);
    free(two);
    free(three);

    return result;
}