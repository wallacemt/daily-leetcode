int* plusOne(int* digits, int digitsSize, int* returnSize) {
    int carry = 1;
    int* result = (int*)malloc(digitsSize * sizeof(int));
    if (!result) return NULL;

    for (int i = digitsSize - 1; i >= 0; i--) {
        int sum = digits[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }

    if (carry) {
        int* newResult = (int*)malloc((digitsSize + 1) * sizeof(int));
        if (!newResult) return NULL;

        newResult[0] = carry;
        memcpy(newResult + 1, result, digitsSize * sizeof(int));
        free(result);
        result = newResult;
        *returnSize = digitsSize + 1;
    } else {
        *returnSize = digitsSize;
    }

    return result;
}