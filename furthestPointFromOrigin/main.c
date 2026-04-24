#include <stdlib.h>

int furthestDistanceFromOrigin(char* moves) {
    int countL = 0, countR = 0, countUnderscore = 0;
    
    for (int i = 0; moves[i]; i++) {
        if (moves[i] == 'L') countL++;
        else if (moves[i] == 'R') countR++;
        else if (moves[i] == '_') countUnderscore++;
    }
    
    int diff = countL > countR ? countL - countR : countR - countL;
    
    return diff + countUnderscore;
}