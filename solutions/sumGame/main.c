bool sumGame(const char* num) {
    const int len = strlen(num);
    const int half = len / 2;

    int diff = 0;

    for (int i = 0; i < len; ++i) {
        const int value = (num[i] == '?')
            ? 9
            : 2 * (num[i] - '0');

        if (i < half) {
            diff += value;
        } else {
            diff -= value;
        }
    }

    return diff != 0;
}