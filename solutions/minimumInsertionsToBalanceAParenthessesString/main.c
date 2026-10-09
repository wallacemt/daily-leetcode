int minInsertions(char* s) {
    int insertions = 0, right_needed = 0;

    for (; *s; s++) {
        if (*s == '(') {
            int odd = right_needed & 1;
            insertions += odd;
            right_needed = right_needed - odd + 2;
        } else {
            right_needed--;
            int underflow = (right_needed >> 31) & 1;
            insertions += underflow;
            right_needed += underflow * 2;
        }
    }

    return insertions + right_needed;
}