#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return *(int *)b - *(int *)a;
}

long long maximumHappinessSum(int* happiness, int happinessSize, int k) {
 
    if (k <= 0 || happinessSize == 0) return 0;
    if (k > happinessSize) k = happinessSize;
    
    qsort(happiness, happinessSize, sizeof(int), compare);
    
    long long res = 0;
    int turn = 0;
    
    for (int i = 0; i < k; ++i) {
        long long currentHappiness = (long long)happiness[i] - turn;
        
        if (currentHappiness > 0) {
            res += currentHappiness;
            turn++; 
        } else {
            break; 
        }
    }
    
    return res;
}