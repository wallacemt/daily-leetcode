#include <math.h>
#include <stdio.h>

long long minNumberOfSeconds(int mountainHeight, int* workerTimes, int workerTimesSize) {
    // Pré-calcular o produto constante
    long long mh_product = (long long)mountainHeight * (mountainHeight + 1) / 2;
    
    // Encontrar maxT e calcular r simultaneamente
    long long maxT = workerTimes[0];
    for (int i = 1; i < workerTimesSize; i++) {
        if (workerTimes[i] > maxT) {
            maxT = workerTimes[i];
        }
    }

    long long l = 1;
    long long r = maxT * mh_product;
    long long ans = r;

    while (l <= r) {
        long long m = l + (r - l) / 2;
        long long tmp = 0;

        // Verificação com early break
        for (int i = 0; i < workerTimesSize; i++) {
            long long t = workerTimes[i];
            long long lim = m / t;
            
            // Usar sqrtl para melhor precisão com long long
            long long k = (long long)((-1.0 + sqrtl(1.0 + 8.0 * lim)) / 2.0 + 1e-9);
            tmp += k;
            
            // Early break se já atingimos o objetivo
            if (tmp >= mountainHeight) {
                break;
            }
        }

        if (tmp >= mountainHeight) {
            ans = m;
            r = m - 1;
        } else {
            l = m + 1;
        }
    }

    return ans;
}