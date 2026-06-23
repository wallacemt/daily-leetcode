char* decodeCiphertext(char* encodedText, int rows) {
    if (rows == 1) {
        return strdup(encodedText);
    }

    int n = strlen(encodedText);
    int cols = n / rows;
    char* dec = (char*)malloc((n + 1) * sizeof(char));
    int dec_ptr = 0;
    int i = 0, j = 0;
    long long k = 0;
    while (k < n) {
        dec[dec_ptr++] = encodedText[k];
        i++;
        if (i == rows) {
            i = 0;
            j++;
        }
        k = (long long)i * (cols + 1) + j;
    }
    dec[dec_ptr] = '\0';
    int len = strlen(dec);
    for (int p = len - 1; p >= 0; p--) {
        if (dec[p] == ' ') {
            dec[p] = '\0';
        } else {
            break;
        }
    }

    return dec;
}
