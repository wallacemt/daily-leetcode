#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int w;
    int h;
    int p;           
    int curr;        
    bool moved;    
    int pos[2];     
    char dir[6];    
} Robot;

Robot* robotCreate(int width, int height) {
    Robot* obj = (Robot*)malloc(sizeof(Robot));
    obj->w = width;
    obj->h = height;
    obj->p = 2 * (width + height - 2);
    obj->curr = 0;
    obj->moved = false;
    return obj;
}

void robotStep(Robot* obj, int num) {
    obj->moved = true;
    obj->curr = (obj->curr + num) % obj->p;
}

int* robotGetPos(Robot* obj, int* retSize) {
    *retSize = 2;
    
    int w = obj->w;
    int h = obj->h;
    int curr = obj->curr;

    if (curr < w) {
        obj->pos[0] = curr;
        obj->pos[1] = 0;
    }
    else if (curr < w + h - 1) {
        obj->pos[0] = w - 1;
        obj->pos[1] = curr - w + 1;
    }
    else if (curr < 2 * w + h - 2) {
        obj->pos[0] = 2 * w + h - 3 - curr;
        obj->pos[1] = h - 1;
    }
    else {
        obj->pos[0] = 0;
        obj->pos[1] = obj->p - curr;
    }
    
    return obj->pos;
}

char* robotGetDir(Robot* obj) {
    if (!obj->moved) {
        return "East";
    }
    
    if (obj->curr == 0) {
        return "South";
    }
    
    int w = obj->w;
    int h = obj->h;
    int curr = obj->curr;
    
    if (curr < w) {
        return "East";
    } else if (curr < w + h - 1) {
        return "North";
    } else if (curr < 2 * w + h - 2) {
        return "West";
    }
    
    return "South";
}

void robotFree(Robot* obj) {
    free(obj);
}