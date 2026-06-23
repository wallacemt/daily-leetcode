#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FOODS 20000
#define HASH_SIZE 50000
#define MAX_CUISINES 1000

typedef struct HashNode {
    char* key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct {
    char* food;
    int rating;
    int index; // index in the foods array
} HeapNode;

typedef struct {
    HeapNode* heap;
    int size;
    int capacity;
} MaxHeap;

typedef struct {
    char* food;
    char* cuisine;
    int rating;
} Food;

typedef struct {
    Food foods[MAX_FOODS];
    int size;
    HashNode* foodToIndex[HASH_SIZE];   
    HashNode* cuisineToHeap[HASH_SIZE];  
    MaxHeap heaps[MAX_CUISINES];
    int heapCount;
} FoodRatings;

unsigned int hash(char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_SIZE;
}

void hashInsert(HashNode** table, char* key, int value) {
    unsigned int index = hash(key);
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    node->key = strdup(key);
    node->value = value;
    node->next = table[index];
    table[index] = node;
}

int hashGet(HashNode** table, char* key) {
    unsigned int index = hash(key);
    HashNode* node = table[index];
    while (node) {
        if (strcmp(node->key, key) == 0) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

MaxHeap* createHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->heap = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void swap(HeapNode* a, HeapNode* b) {
    HeapNode temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(MaxHeap* heap, int index) {
    if (index == 0) return;
    int parent = (index - 1) / 2;
    
    if (heap->heap[index].rating > heap->heap[parent].rating ||
        (heap->heap[index].rating == heap->heap[parent].rating &&
         strcmp(heap->heap[index].food, heap->heap[parent].food) < 0)) {
        swap(&heap->heap[index], &heap->heap[parent]);
        heapifyUp(heap, parent);
    }
}

void heapifyDown(MaxHeap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    
    if (left < heap->size) {
        if (heap->heap[left].rating > heap->heap[largest].rating ||
            (heap->heap[left].rating == heap->heap[largest].rating &&
             strcmp(heap->heap[left].food, heap->heap[largest].food) < 0)) {
            largest = left;
        }
    }
    
    if (right < heap->size) {
        if (heap->heap[right].rating > heap->heap[largest].rating ||
            (heap->heap[right].rating == heap->heap[largest].rating &&
             strcmp(heap->heap[right].food, heap->heap[largest].food) < 0)) {
            largest = right;
        }
    }
    
    if (largest != index) {
        swap(&heap->heap[index], &heap->heap[largest]);
        heapifyDown(heap, largest);
    }
}

void heapInsert(MaxHeap* heap, char* food, int rating, int index) {
    if (heap->size >= heap->capacity) return;
    
    heap->heap[heap->size].food = food;
    heap->heap[heap->size].rating = rating;
    heap->heap[heap->size].index = index;
    heapifyUp(heap, heap->size);
    heap->size++;
}

FoodRatings* foodRatingsCreate(char** foods, int foodsSize, char** cuisines, int cuisinesSize, int* ratings, int ratingsSize) {
    FoodRatings* obj = (FoodRatings*)malloc(sizeof(FoodRatings));
    obj->size = foodsSize;
    obj->heapCount = 0; 
    for (int i = 0; i < HASH_SIZE; i++) {
        obj->foodToIndex[i] = NULL;
        obj->cuisineToHeap[i] = NULL;
    }
     
    for (int i = 0; i < foodsSize; i++) {
        obj->foods[i].food = strdup(foods[i]);
        obj->foods[i].cuisine = strdup(cuisines[i]);
        obj->foods[i].rating = ratings[i];
        hashInsert(obj->foodToIndex, foods[i], i);
         
        int heapIndex = hashGet(obj->cuisineToHeap, cuisines[i]);
        if (heapIndex == -1) { 
            obj->heaps[obj->heapCount] = *createHeap(foodsSize);
            hashInsert(obj->cuisineToHeap, cuisines[i], obj->heapCount);
            heapIndex = obj->heapCount;
            obj->heapCount++;
        }
        
        heapInsert(&obj->heaps[heapIndex], obj->foods[i].food, ratings[i], i);
    }
    
    return obj;
}

void foodRatingsChangeRating(FoodRatings* obj, char* food, int newRating) {
    int foodIndex = hashGet(obj->foodToIndex, food);
    if (foodIndex == -1) return;
    
    obj->foods[foodIndex].rating = newRating;
     
    int heapIndex = hashGet(obj->cuisineToHeap, obj->foods[foodIndex].cuisine);
    if (heapIndex != -1) {
        MaxHeap* heap = &obj->heaps[heapIndex];
        
        for (int i = 0; i < heap->size; i++) {
            if (heap->heap[i].index == foodIndex) {
                heap->heap[i].rating = newRating;
                heapifyUp(heap, i);
                heapifyDown(heap, i);
                break;
            }
        }
    }
}

char* foodRatingsHighestRated(FoodRatings* obj, char* cuisine) {
    int heapIndex = hashGet(obj->cuisineToHeap, cuisine);
    if (heapIndex == -1) return NULL;
    
    MaxHeap* heap = &obj->heaps[heapIndex];
    if (heap->size == 0) return NULL;
    
    return heap->heap[0].food;
}

void foodRatingsFree(FoodRatings* obj) {
   
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* node = obj->foodToIndex[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
        
        node = obj->cuisineToHeap[i];
        while (node) {
            HashNode* temp = node;
            node = node->next;
            free(temp->key);
            free(temp);
        }
    }
     
    for (int i = 0; i < obj->heapCount; i++) {
        free(obj->heaps[i].heap);
    } 
    for (int i = 0; i < obj->size; i++) {
        free(obj->foods[i].food);
        free(obj->foods[i].cuisine);
    }
    
    free(obj);
}