#define max(a, b) a < b ? b : a;
int largestAltitude(int* gain, int gainSize) {
    int alt = 0, res = 0;
        for (int i = 0; i < gainSize; i++){
            alt += gain[i];
            res = max(res, alt);
        }
        return res;
}