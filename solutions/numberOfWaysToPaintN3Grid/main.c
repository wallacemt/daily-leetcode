#include <stdlib.h>
#include <string.h>

#define MOD 1000000007

typedef struct {
    long long data[2][2];
} Matrix;

Matrix matrixMultiply(Matrix A, Matrix B) {
    Matrix C;
    memset(C.data, 0, sizeof(C.data));
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                C.data[i][j] = (C.data[i][j] + 
                                A.data[i][k] * B.data[k][j]) % MOD;
            }
        }
    }
    
    return C;
}

Matrix matrixPower(Matrix base, int n) {
    Matrix result;
    result.data[0][0] = 1;
    result.data[0][1] = 0;
    result.data[1][0] = 0;
    result.data[1][1] = 1;
    
    while (n > 0) {
        if (n % 2 == 1) {
            result = matrixMultiply(result, base);
        }
        base = matrixMultiply(base, base);
        n /= 2;
    }
    
    return result;
}

int numOfWays(int n) {
    Matrix matrix;
    matrix.data[0][0] = 2;
    matrix.data[0][1] = 2;
    matrix.data[1][0] = 2;
    matrix.data[1][1] = 3;
    
    Matrix result = matrixPower(matrix, n - 1);
    
    long long A = (6LL * result.data[0][0] + 6LL * result.data[0][1]) % MOD;
    long long B = (6LL * result.data[1][0] + 6LL * result.data[1][1]) % MOD;
    
    return (int)((A + B) % MOD);
}