#include <stdlib.h>

typedef struct {
    int* prefix;
    int size;      
    int capacity;
} ProductOfNumbers;

ProductOfNumbers* productOfNumbersCreate() {
    ProductOfNumbers* obj = malloc(sizeof(ProductOfNumbers));
    if (!obj) return NULL;

    obj->capacity = 32;
    obj->size = 1;
    obj->prefix = malloc(obj->capacity * sizeof(int));
    if (!obj->prefix) {
        free(obj);
        return NULL;
    }

    obj->prefix[0] = 1; 
    return obj;
}

void productOfNumbersAdd(ProductOfNumbers* obj, int num) {
    if (!obj) return;
 
    if (num == 0) {
        obj->size = 1;
        return;
    }

    if (obj->size == obj->capacity) {
        int newCapacity = obj->capacity * 2;
        int* newPrefix = realloc(obj->prefix, newCapacity * sizeof(int));
        if (!newPrefix) return;
        obj->prefix = newPrefix;
        obj->capacity = newCapacity;
    }

    obj->prefix[obj->size] = obj->prefix[obj->size - 1] * num;
    obj->size++;
}

int productOfNumbersGetProduct(ProductOfNumbers* obj, int k) { 
    if (!obj || k >= obj->size) {
        return 0;
    }
 
    return obj->prefix[obj->size - 1] / obj->prefix[obj->size - 1 - k];
}

void productOfNumbersFree(ProductOfNumbers* obj) {
    if (obj) {
        free(obj->prefix);
        free(obj);
    }
}