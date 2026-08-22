bool checkDivisibility(int n) {
    if (n <= 0) {
        return true; 
    }

    long long sum = 0;
    long long product = 1;

    for (int x = n; x > 0; x /= 10) {
        const int digit = x % 10;

        sum += digit; 
        if (product != 0) {
            product *= digit;
        }
    }

    const long long divisor = sum + product;

    return n % divisor == 0;
}
