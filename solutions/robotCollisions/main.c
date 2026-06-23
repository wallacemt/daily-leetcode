#include <stdlib.h>

typedef struct {
    int idx, pos, hp, dir;
} Robot;

int cmpPos(const void* a, const void* b) {
    return ((Robot*)a)->pos - ((Robot*)b)->pos;
}

int cmpIdx(const void* a, const void* b) {
    return ((Robot*)a)->idx - ((Robot*)b)->idx;
}

int* survivedRobotsHealths(int* positions, int positionsSize, int* healths, int healthsSize, char* directions, int* returnSize) {
    Robot* robots = (Robot*)malloc(positionsSize * sizeof(Robot));
    
    for (int i = 0; i < positionsSize; i++) {
        robots[i] = (Robot){i, positions[i], healths[i], directions[i] == 'R'};
    }

    qsort(robots, positionsSize, sizeof(Robot), cmpPos);

    int l = 0;
    for (int r = 0; r < positionsSize; r++) {
        Robot curr = robots[r];
        
        if (curr.dir) {
            robots[l++] = curr;
            continue;
        }
        
        while (l > 0 && robots[l - 1].dir && curr.hp > 0) {
            int diff = robots[l - 1].hp - curr.hp;
            if (diff > 0) {
                robots[l - 1].hp--;
                curr.hp = 0;
            } else if (diff < 0) {
                curr.hp--;
                l--;
            } else {
                curr.hp = 0;
                l--;
            }
        }
        
        if (curr.hp > 0) robots[l++] = curr;
    }

    qsort(robots, l, sizeof(Robot), cmpIdx);

    *returnSize = l;
    int* res = (int*)malloc(l * sizeof(int));
    for (int i = 0; i < l; i++) res[i] = robots[i].hp;

    free(robots);
    return res;
}