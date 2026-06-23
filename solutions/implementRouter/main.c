#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_SIZE 65536 
#define INITIAL_CAPACITY 16

typedef struct Packet {
    int source;
    int destination;
    int timestamp;
    struct Packet* next;
    struct Packet* prev; 
} Packet;

typedef struct KeyNode {
    int source, dest, timestamp;  
    struct KeyNode* next;
} KeyNode;

typedef struct DestInfo {
    int* timestamps;
    int size;
    int capacity;
} DestInfo;

typedef struct Router {
    int memoryLimit;
    int size;
    Packet* head;
    Packet* tail;
    KeyNode* packetSet[HASH_SIZE];
    DestInfo* destMap[HASH_SIZE];
} Router;

static inline unsigned int hashPacket(int source, int dest, int ts) {
    unsigned int hash = (unsigned int)source;
    hash = hash * 31 + (unsigned int)dest;
    hash = hash * 31 + (unsigned int)ts;
    return hash & (HASH_SIZE - 1);  
}

static inline unsigned int hashInt(int x) {
    return ((unsigned int)x) & (HASH_SIZE - 1);
}

bool packetExists(Router* obj, int source, int dest, int ts) {
    unsigned int h = hashPacket(source, dest, ts);
    KeyNode* cur = obj->packetSet[h];
    while (cur) {
        if (cur->source == source && cur->dest == dest && cur->timestamp == ts) 
            return true;
        cur = cur->next;
    }
    return false;
}

void packetInsert(Router* obj, int source, int dest, int ts) {
    unsigned int h = hashPacket(source, dest, ts);
    KeyNode* node = malloc(sizeof(KeyNode));
    node->source = source;
    node->dest = dest;
    node->timestamp = ts;
    node->next = obj->packetSet[h];
    obj->packetSet[h] = node;
}

void packetRemove(Router* obj, int source, int dest, int ts) {
    unsigned int h = hashPacket(source, dest, ts);
    KeyNode *cur = obj->packetSet[h], *prev = NULL;
    while (cur) {
        if (cur->source == source && cur->dest == dest && cur->timestamp == ts) {
            if (prev) prev->next = cur->next;
            else obj->packetSet[h] = cur->next;
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }
}

DestInfo* createDest() {
    DestInfo* d = malloc(sizeof(DestInfo));
    d->timestamps = malloc(INITIAL_CAPACITY * sizeof(int));
    d->size = 0;
    d->capacity = INITIAL_CAPACITY;
    return d;
}

void addDestTimestamp(Router* obj, int dest, int ts) {
    unsigned int h = hashInt(dest);
    DestInfo* d = obj->destMap[h];
    if (!d) {
        d = createDest();
        obj->destMap[h] = d;
    }
    if (d->size == d->capacity) {
        d->capacity <<= 1;  
        d->timestamps = realloc(d->timestamps, d->capacity * sizeof(int));
    }
    
    int pos = d->size;
    while (pos > 0 && d->timestamps[pos - 1] > ts) {
        d->timestamps[pos] = d->timestamps[pos - 1];
        pos--;
    }
    d->timestamps[pos] = ts;
    d->size++;
}

void removeDestTimestamp(Router* obj, int dest, int ts) {
    unsigned int h = hashInt(dest);
    DestInfo* d = obj->destMap[h];
    if (!d) return;
    
    int left = 0, right = d->size - 1, pos = -1;
    while (left <= right) {
        int mid = left + ((right - left) >> 1);
        if (d->timestamps[mid] == ts) {
            pos = mid;
            break;
        } else if (d->timestamps[mid] < ts) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    if (pos == -1) return;
    
    memmove(&d->timestamps[pos], &d->timestamps[pos + 1], 
            (d->size - pos - 1) * sizeof(int));
    d->size--;
    
    if (d->size == 0) {
        free(d->timestamps);
        free(d);
        obj->destMap[h] = NULL;
    }
}

Router* routerCreate(int memoryLimit) {
    Router* obj = malloc(sizeof(Router));
    obj->memoryLimit = memoryLimit;
    obj->size = 0;
    obj->head = obj->tail = NULL;
    memset(obj->packetSet, 0, sizeof(obj->packetSet));
    memset(obj->destMap, 0, sizeof(obj->destMap));
    return obj;
}

bool routerAddPacket(Router* obj, int source, int dest, int ts) {
    if (packetExists(obj, source, dest, ts)) {
        return false;
    }
    if (obj->size == obj->memoryLimit) {
        Packet* old = obj->head;
        obj->head = old->next;
        if (obj->head) obj->head->prev = NULL;
        else obj->tail = NULL;
        
        packetRemove(obj, old->source, old->destination, old->timestamp);
        removeDestTimestamp(obj, old->destination, old->timestamp);
        free(old);
        obj->size--;
    }

    Packet* p = malloc(sizeof(Packet));
    p->source = source;
    p->destination = dest;
    p->timestamp = ts;
    p->next = NULL;
    p->prev = obj->tail;
    
    if (obj->tail) obj->tail->next = p;
    else obj->head = p;
    obj->tail = p;
    obj->size++;

    packetInsert(obj, source, dest, ts);
    addDestTimestamp(obj, dest, ts);
    return true;
}

int* routerForwardPacket(Router* obj, int* retSize) {
    if (!obj->head) {
        *retSize = 0;
        return NULL;
    }
    
    Packet* p = obj->head;
    obj->head = p->next;
    if (obj->head) obj->head->prev = NULL;
    else obj->tail = NULL;
    obj->size--;

    packetRemove(obj, p->source, p->destination, p->timestamp);
    removeDestTimestamp(obj, p->destination, p->timestamp);

    int* res = malloc(3 * sizeof(int));
    res[0] = p->source;
    res[1] = p->destination;
    res[2] = p->timestamp;
    *retSize = 3;
    free(p);
    return res;
}

int routerGetCount(Router* obj, int dest, int startTime, int endTime) {
    unsigned int h = hashInt(dest);
    DestInfo* d = obj->destMap[h];
    if (!d) return 0;
    
    int left = 0, right = d->size, start = d->size;
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (d->timestamps[mid] >= startTime) {
            start = mid;
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    left = 0; right = d->size; int end = 0;
    while (left < right) {
        int mid = left + ((right - left) >> 1);
        if (d->timestamps[mid] <= endTime) {
            end = mid + 1;
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    
    return end - start;
}

void routerFree(Router* obj) {
    while (obj->head) {
        Packet* tmp = obj->head;
        obj->head = obj->head->next;
        free(tmp);
    }
    for (int i = 0; i < HASH_SIZE; i++) {
        KeyNode* k = obj->packetSet[i];
        while (k) {
            KeyNode* t = k;
            k = k->next;
            free(t);
        }
        DestInfo* d = obj->destMap[i];
        if (d) {
            free(d->timestamps);
            free(d);
        }
    }
    free(obj);
}