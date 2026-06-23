#include <math.h>

int binaryGap(int n) {
    int last = -1;
    int max = 0;
    int pos = 0;
    
    while (n > 0) {
        if (n & 1) {
            if (last != -1) {
                int curr = pos - last;
                max = fmax(max, curr); 
            }
            last = pos;
        }
        pos++;
        n >>= 1;
    }
    
    return max;
}
