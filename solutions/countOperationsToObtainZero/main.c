int countOperations(int num1, int num2) {
    long long ops = 0;
    while (num1 && num2) {
        if (num1 >= num2) {
            ops += num1 / num2;
            num1 %= num2;
        } else {
            ops += num2 / num1;
            num2 %= num1;
        }
    }
    return (int)ops;
}
