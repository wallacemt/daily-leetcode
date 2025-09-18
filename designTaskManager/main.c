#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int priority;
    int taskId;
    int userId;
} HeapNode;

typedef struct {
    int taskId;
    int userId;
    int priority;
    int valid;
} TaskEntry;

typedef struct {
    HeapNode* heap;
    int heapSize;
    int heapCap;
    TaskEntry* tasks;
    int taskCap;
    char** delSet;
    int delSize;
    int delCap;
} TaskManager;

static inline void heapSwap(HeapNode* a, HeapNode* b) {
    HeapNode t = *a; *a = *b; *b = t;
}

void heapifyUp(TaskManager* obj, int idx) {
    HeapNode* heap = obj->heap;
    while (idx > 0) {
        int parent = (idx - 1) >> 1;
        HeapNode *p = &heap[parent], *c = &heap[idx];
        if (p->priority < c->priority || (p->priority == c->priority && p->taskId < c->taskId)) {
            heapSwap(p, c);
            idx = parent;
        } else break;
    }
}

void heapifyDown(TaskManager* obj, int idx) {
    HeapNode* heap = obj->heap;
    int heapSize = obj->heapSize;
    
    while (1) {
        int left = (idx << 1) + 1;
        int right = left + 1;
        int largest = idx;
        
        if (left < heapSize) {
            HeapNode *l = &heap[left], *cur = &heap[largest];
            if (l->priority > cur->priority || (l->priority == cur->priority && l->taskId > cur->taskId))
                largest = left;
        }
        if (right < heapSize) {
            HeapNode *r = &heap[right], *lg = &heap[largest];
            if (r->priority > lg->priority || (r->priority == lg->priority && r->taskId > lg->taskId))
                largest = right;
        }
        if (largest != idx) {
            heapSwap(&heap[idx], &heap[largest]);
            idx = largest;
        } else break;
    }
}

void heapPush(TaskManager* obj, int priority, int taskId, int userId) {
    if (obj->heapSize >= obj->heapCap) {
        obj->heapCap <<= 1;
        obj->heap = realloc(obj->heap, obj->heapCap * sizeof(HeapNode));
    }
    obj->heap[obj->heapSize] = (HeapNode){priority, taskId, userId};
    heapifyUp(obj, obj->heapSize++);
}

static inline HeapNode heapTop(TaskManager* obj) {
    return obj->heap[0];
}

void heapPop(TaskManager* obj) {
    if (obj->heapSize == 0) return;
    obj->heap[0] = obj->heap[--obj->heapSize];
    heapifyDown(obj, 0);
}

static inline char* generateKey(int taskId, int priority) {
    char* buf = malloc(24);
    sprintf(buf, "%d:%d", taskId, priority);
    return buf;
}

int delSetContains(TaskManager* obj, const char* key) {
    char** delSet = obj->delSet;
    int delSize = obj->delSize;
    for (int i = 0; i < delSize; i++) {
        if (strcmp(delSet[i], key) == 0) return 1;
    }
    return 0;
}

void delSetInsert(TaskManager* obj, char* key) {
    if (obj->delSize >= obj->delCap) {
        obj->delCap <<= 1;
        obj->delSet = realloc(obj->delSet, obj->delCap * sizeof(char*));
    }
    obj->delSet[obj->delSize++] = key;
}

void delSetErase(TaskManager* obj, const char* key) {
    char** delSet = obj->delSet;
    for (int i = 0; i < obj->delSize; i++) {
        if (strcmp(delSet[i], key) == 0) {
            free(delSet[i]);
            delSet[i] = delSet[--obj->delSize];
            return;
        }
    }
}

TaskManager* taskManagerCreate(int** tasks, int tasksSize, int* tasksColSize) {
    TaskManager* obj = malloc(sizeof(TaskManager));
    obj->heapCap = 128;
    obj->heapSize = 0;
    obj->heap = malloc(obj->heapCap * sizeof(HeapNode));
    obj->taskCap = 100005;
    obj->tasks = calloc(obj->taskCap, sizeof(TaskEntry));
    obj->delCap = 128;
    obj->delSize = 0;
    obj->delSet = malloc(obj->delCap * sizeof(char*));
    
    TaskEntry* tasks_arr = obj->tasks;
    for (int i = 0; i < tasksSize; i++) {
        int userId = tasks[i][0];
        int taskId = tasks[i][1];
        int priority = tasks[i][2];
        tasks_arr[taskId] = (TaskEntry){taskId, userId, priority, 1};
        heapPush(obj, priority, taskId, userId);
    }
    return obj;
}

void taskManagerAdd(TaskManager* obj, int userId, int taskId, int priority) {
    obj->tasks[taskId] = (TaskEntry){taskId, userId, priority, 1};
    heapPush(obj, priority, taskId, userId);
}

void taskManagerEdit(TaskManager* obj, int taskId, int newPriority) {
    TaskEntry* task = &obj->tasks[taskId];
    if (taskId < obj->taskCap && task->valid) {
        int oldPriority = task->priority;
        if (newPriority != oldPriority) {
            char* key = generateKey(taskId, oldPriority);
            delSetInsert(obj, key);
            task->priority = newPriority;
            heapPush(obj, newPriority, taskId, task->userId);
        }
    }
}

void taskManagerRmv(TaskManager* obj, int taskId) {
    TaskEntry* task = &obj->tasks[taskId];
    if (taskId < obj->taskCap && task->valid) {
        char* key = generateKey(taskId, task->priority);
        delSetInsert(obj, key);
        task->valid = 0;
    }
}

int taskManagerExecTop(TaskManager* obj) {
    while (obj->heapSize > 0) {
        HeapNode top = heapTop(obj);
        char* key = generateKey(top.taskId, top.priority);
        if (delSetContains(obj, key)) {
            heapPop(obj);
            delSetErase(obj, key);
            free(key);
        } else {
            heapPop(obj);
            obj->tasks[top.taskId].valid = 0;
            free(key);
            return top.userId;
        }
    }
    return -1;
}

void taskManagerFree(TaskManager* obj) {
    for (int i = 0; i < obj->delSize; i++) free(obj->delSet[i]);
    free(obj->delSet);
    free(obj->heap);
    free(obj->tasks);
    free(obj);
}