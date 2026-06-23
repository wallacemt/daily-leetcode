#include <string.h>

int ceilDiv(int numerador, int denominador) {
    return (numerador + denominador - 1) / denominador;
}

int minOperations(char *S, int K) {
    if (S == NULL) return -1;

    int N = strlen(S);
    int zeroCount = 0;

    for (int i = 0; i < N; i++) {
        if (S[i] == '0') zeroCount++;
    }

    if (N == K) {
        if (zeroCount == 0) return 0;      // Sem '0's
        if (zeroCount == N) return 1;      // Todos '0's
        return -1;                         // Impossível
    }

    int minOps = INT_MAX;
    int onesCount = N - zeroCount;

    if (zeroCount % 2 == 0) {
        int ops = ceilDiv(zeroCount, K);
        ops = (ops > ceilDiv(zeroCount, N - K)) ? ops : ceilDiv(zeroCount, N - K);
        if (ops % 2 == 1) ops++;  // Ajusta para par
        minOps = (ops < minOps) ? ops : minOps;
    }

    if (zeroCount % 2 == K % 2) {
        int ops = ceilDiv(zeroCount, K);
        ops = (ops > ceilDiv(onesCount, N - K)) ? ops : ceilDiv(onesCount, N - K);
        if (ops % 2 == 0) ops++;  // Ajusta para ímpar
        minOps = (ops < minOps) ? ops : minOps;
    }

    return (minOps == INT_MAX) ? -1 : minOps;
}