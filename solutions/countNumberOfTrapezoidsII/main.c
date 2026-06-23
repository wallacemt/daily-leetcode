#include <stdlib.h>
#include <math.h>

typedef struct {
    long long dx;
    long long dy;
    long long c;
} Segment;

long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

int compareSegments(const void* a, const void* b) {
    Segment* sa = (Segment*)a;
    Segment* sb = (Segment*)b;
    
    if (sa->dx != sb->dx) return (sa->dx > sb->dx) ? 1 : -1;
    if (sa->dy != sb->dy) return (sa->dy > sb->dy) ? 1 : -1;
    if (sa->c != sb->c) return (sa->c > sb->c) ? 1 : -1;
    return 0;
}

void fillSegments(int** points, int pointsSize, Segment* segments, int normalize) {
    int k = 0;
    for (int i = 0; i < pointsSize; i++) {
        for (int j = i + 1; j < pointsSize; j++) {
            long long dx = points[j][0] - points[i][0];
            long long dy = points[j][1] - points[i][1];
            
            if (normalize) {
                long long common = gcd(llabs(dx), llabs(dy));
                dx /= common;
                dy /= common;
            }
            
            if (dx < 0 || (dx == 0 && dy < 0)) {
                dx = -dx;
                dy = -dy;
            }
            
            segments[k++] = (Segment){dx, dy, dy * points[i][0] - dx * points[i][1]};
        }
    }
}

int countParallelPairs(Segment* segments, int k) {
    int count = 0;
    
    for (int i = 0; i < k; ) {
        int j = i;
        int currentCount = 0;
        
        while (j < k && segments[i].dx == segments[j].dx && segments[i].dy == segments[j].dy) {
            int l = j;
            while (l < k && segments[i].dx == segments[l].dx && 
                            segments[i].dy == segments[l].dy && 
                            segments[j].c == segments[l].c) {
                l++;
            }
            int lineCount = l - j;
            count += currentCount * lineCount;
            currentCount += lineCount;
            j = l;
        }
        i = j;
    }
    
    return count;
}

int countTrapezoids(int** points, int pointsSize, int* pointsColSize) {
    if (pointsSize < 4) return 0;
    
    int maxSegments = pointsSize * (pointsSize - 1) / 2;
    Segment* segments = (Segment*)malloc(sizeof(Segment) * maxSegments);

    fillSegments(points, pointsSize, segments, 1);
    qsort(segments, maxSegments, sizeof(Segment), compareSegments);
    int totalTrapezoids = countParallelPairs(segments, maxSegments);

    fillSegments(points, pointsSize, segments, 0);
    qsort(segments, maxSegments, sizeof(Segment), compareSegments);
    int parallelograms = countParallelPairs(segments, maxSegments);
    
    free(segments);
    
    return totalTrapezoids - (parallelograms / 2);
}
