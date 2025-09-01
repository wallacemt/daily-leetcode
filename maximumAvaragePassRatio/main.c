#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int pass;
    int total;
    double gain;
} Class;

double calculateGain(int pass, int total) {
    return (double)(pass + 1) / (total + 1) - (double)pass / total;
}

void heapify(Class* heap, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n && heap[left].gain > heap[largest].gain)
        largest = left;
    
    if (right < n && heap[right].gain > heap[largest].gain)
        largest = right;
    
    if (largest != i) {
        Class temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        heapify(heap, n, largest);
    }
}

void buildHeap(Class* heap, int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

void extractMax(Class* heap, int* n) {
    heap[0] = heap[*n - 1];
    (*n)--;
    heapify(heap, *n, 0);
}

void insertAndRebalance(Class* heap, int n, int index) {
    int i = index;
    while (i > 0 && heap[(i - 1) / 2].gain < heap[i].gain) {
        Class temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

double maxAverageRatio(int** classes, int classesSize, int* classesColSize, int extraStudents) {
   
    Class* heap = (Class*)malloc(classesSize * sizeof(Class));
    
    for (int i = 0; i < classesSize; i++) {
        heap[i].pass = classes[i][0];
        heap[i].total = classes[i][1];
        heap[i].gain = calculateGain(classes[i][0], classes[i][1]);
    }
    
    buildHeap(heap, classesSize);
    
    for (int i = 0; i < extraStudents; i++) {
        
        Class maxClass = heap[0];
        
        maxClass.pass++;
        maxClass.total++;
        maxClass.gain = calculateGain(maxClass.pass, maxClass.total);
        
        heap[0] = maxClass;
        heapify(heap, classesSize, 0);
    }
    
    double totalRatio = 0.0;
    for (int i = 0; i < classesSize; i++) {
        totalRatio += (double)heap[i].pass / heap[i].total;
    }
    
    free(heap);
    return totalRatio / classesSize;
}