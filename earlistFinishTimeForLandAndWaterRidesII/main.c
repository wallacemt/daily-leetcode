#include <limits.h>

int calculate(int* start1, int* dur1, int size1, int* start2, int* dur2, int size2) {
    if (size1 == 0 || size2 == 0) {
        return INT_MAX;
    }

    int first_end = start1[0] + dur1[0];
    for (int i = 1; i < size1; i++) {
        int end = start1[i] + dur1[i];
        if (end < first_end) {
            first_end = end;
        }
    }

    int ans = INT_MAX;
    for (int i = 0; i < size2; i++) {
        int start = first_end > start2[i] ? first_end : start2[i];
        int finish = start + dur2[i];
        
        if (finish < ans) {
            ans = finish;
        }
    }
    
    return ans;
}

int earliestFinishTime(int* landStartTime, int landStartTimeSize, 
                       int* landDuration, int landDurationSize, 
                       int* waterStartTime, int waterStartTimeSize, 
                       int* waterDuration, int waterDurationSize) {
  
    if (landStartTimeSize == 0 || waterStartTimeSize == 0) {
        return INT_MAX;
    }

    int land_first = calculate(
        landStartTime,
        landDuration,
        landStartTimeSize,
        waterStartTime,
        waterDuration,
        waterStartTimeSize
    );

    int water_first = calculate(
        waterStartTime,
        waterDuration,
        waterStartTimeSize,
        landStartTime,
        landDuration,
        landStartTimeSize
    );

    return land_first < water_first ? land_first : water_first;
}