#include <stdbool.h>
#include <limits.h>
#include <math.h>
 
bool checkOverlap(int radius, int xCenter, int yCenter, 
                  int x1, int y1, int x2, int y2) {
    
    if (radius < 0) {
        return false;
    }
 
    if (x1 > x2) {
        int temp = x1;
        x1 = x2;
        x2 = temp;
    }
    if (y1 > y2) {
        int temp = y1;
        y1 = y2;
        y2 = temp;
    }
 
    int x = xCenter;
    int y = yCenter;
 
    if (x < x1) x = x1;
    if (x > x2) x = x2;

    if (y < y1) y = y1;
    if (y > y2) y = y2;

     
    long long dx = (long long)xCenter - x;
    long long dy = (long long)yCenter - y;
    long long radiusSq = (long long)radius * radius;

    
    return dx * dx + dy * dy <= radiusSq;
}