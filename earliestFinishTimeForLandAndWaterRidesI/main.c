inline int min(int a, int b) { 
  return a < b ? a : b; 
}

inline int max(int a, int b) { 
  return a > b ? a : b; 
}

static int computeSequenceTime(int* start1, int size1, int* duration1,
                                int* start2, int size2, int* duration2) {

  int finish1 = INT_MAX;
  for (int i = 0; i < size1; i++) {
    finish1 = min(finish1, start1[i] + duration1[i]);
  }

  int minFinish2 = INT_MAX;
  for (int j = 0; j < size2; j++) {
    int finishTime = max(finish1, start2[j]) + duration2[j];
    minFinish2 = min(minFinish2, finishTime);
  }

  return minFinish2;
}

int earliestFinishTime(int* landStartTime, int landStartTimeSize,
                       int* landDuration, int landDurationSize,
                       int* waterStartTime, int waterStartTimeSize,
                       int* waterDuration, int waterDurationSize) {
  
  int landToWater = computeSequenceTime(
    landStartTime, landStartTimeSize, landDuration,
    waterStartTime, waterStartTimeSize, waterDuration
  );

  int waterToLand = computeSequenceTime(
    waterStartTime, waterStartTimeSize, waterDuration,
    landStartTime, landStartTimeSize, landDuration
  );

  return min(landToWater, waterToLand);
}