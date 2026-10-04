bool checkValidString(char* s) {
    int n = strlen(s);

    int* left = (int*)malloc(n * sizeof(int));
    int* star = (int*)malloc(n * sizeof(int));

    int leftTop = 0;
    int starTop = 0;

    for (int i = 0; i < n; i++) {
        if (s[i] == '(') {
            left[leftTop++] = i;
        }
        else if (s[i] == '*') {
            star[starTop++] = i;
        }
        else if (s[i] == ')') {
            if (leftTop > 0) {
                leftTop--;
            }
            else if (starTop > 0) {
                starTop--;
            }
            else {
                free(left);
                free(star);
                return false;
            }
        }
    }

    while (leftTop > 0 && starTop > 0 &&
           left[leftTop - 1] < star[starTop - 1]) {
        leftTop--;
        starTop--;
    }

    bool result = leftTop == 0;

    free(left);
    free(star);

    return result;
}