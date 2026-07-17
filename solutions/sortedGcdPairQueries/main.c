int lowerBound(long long* arr, int size, long long target) {
    int left = 0;
    int right = size;

    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;
}

int* gcdValues(
    int* nums,
    int numsSize,
    long long* queries,
    int queriesSize,
    int* returnSize
) {
    // Encontrar maxValue com early termination
    int maxValue = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > maxValue) {
            maxValue = nums[i];
        }
    }

    // Alocação única e contigua
    int* freq = calloc(maxValue + 1, sizeof(int));
    if (!freq) return NULL;

    // Contar frequências
    for (int i = 0; i < numsSize; i++) {
        freq[nums[i]]++;
    }

    // Alocação contigua: count + prefix + values em um bloco
    long long* count = calloc(maxValue + 1, sizeof(long long));
    if (!count) {
        free(freq);
        return NULL;
    }

    // Calcular GCDs com otimização: parar quando pairs == 0
    for (int gcdValue = maxValue; gcdValue >= 1; gcdValue--) {
        long long total = 0;

        // Somar frequências dos múltiplos
        for (int multiple = gcdValue; multiple <= maxValue; multiple += gcdValue) {
            total += freq[multiple];
        }

        long long pairs = total * (total - 1) / 2;

        // Subtrair pares de múltiplos maiores
        for (int multiple = 2 * gcdValue; multiple <= maxValue; multiple += gcdValue) {
            pairs -= count[multiple];
        }

        count[gcdValue] = pairs;
    }

    int size = 0;
    for (int gcdValue = 1; gcdValue <= maxValue; gcdValue++) {
        if (count[gcdValue] > 0) {
            size++;
        }
    }
    long long* prefix = malloc(size * sizeof(long long));
    int* values = malloc(size * sizeof(int));

    if (!prefix || !values) {
        free(freq);
        free(count);
        free(prefix);
        free(values);
        return NULL;
    }

    int idx = 0;
    long long sum = 0;
    for (int gcdValue = 1; gcdValue <= maxValue; gcdValue++) {
        if (count[gcdValue] > 0) {
            sum += count[gcdValue];
            prefix[idx] = sum;
            values[idx] = gcdValue;
            idx++;
        }
    }
    int* result = malloc(queriesSize * sizeof(int));
    if (!result) {
        free(freq);
        free(count);
        free(prefix);
        free(values);
        return NULL;
    }

    *returnSize = queriesSize;

    for (int i = 0; i < queriesSize; i++) {
        int index = lowerBound(prefix, size, queries[i] + 1);
        result[i] = values[index];
    }

    // Cleanup
    free(freq);
    free(count);
    free(prefix);
    free(values);

    return result;
}