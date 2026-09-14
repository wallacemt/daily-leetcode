#include <stdbool.h>
 
bool isRectangleOverlap(int* rect1, int rect1Size, int* rect2, int rect2Size) {
    return !(
        rect1[2] <= rect2[0] ||  // rect1x2 <= rect2x1
        rect1[0] >= rect2[2] ||  // rect1x1 >= rect2x2
        rect1[3] <= rect2[1] ||  // rect1y2 <= rect2y1
        rect1[1] >= rect2[3]     // rect1y1 >= rect2y2
    );
}