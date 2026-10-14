char* maxSumOfSquares(int num, int sum) {
    if (sum > 9 * num) {
        char* empty = (char*)malloc(1);
        empty[0] = '\0';
        return empty;
    }

    char* ans = (char*)malloc((num + 1) * sizeof(char));
    memset(ans, '0', num);
    ans[num] = '\0';

    int q = sum / 9;
    int r = sum % 9;
 
    for (int i = 0; i < q; i++)
        ans[i] = '9';
 
    if (r > 0)
        ans[q] = '0' + r;

    return ans;
}
