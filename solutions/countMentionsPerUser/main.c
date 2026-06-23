#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* a, const void* b) {
    char** x = *(char***)a;
    char** y = *(char***)b;
    int t1 = atoi(x[1]), t2 = atoi(y[1]);
    if (t1 != t2)
        return t1 - t2;
    int p1 = (x[0][0] == 'M');
    int p2 = (y[0][0] == 'M');
    return p1 - p2;
}

int* countMentions(int numberOfUsers, char*** events, int eventsSize,
                   int* eventsColSize, int* returnSize) {
    qsort(events, eventsSize, sizeof(char**), cmp);

    int* ans = calloc(numberOfUsers, sizeof(int));
    bool* online = malloc(numberOfUsers * sizeof(bool));
    for (int i = 0; i < numberOfUsers; i++)
        online[i] = true;

    int heap[200][2], hsz = 0;

    for (int e = 0; e < eventsSize; e++) {
        int time = atoi(events[e][1]);

        int writeIdx = 0;
        for (int i = 0; i < hsz; i++) {
            if (heap[i][0] <= time) {
                online[heap[i][1]] = true;
            } else {
                heap[writeIdx][0] = heap[i][0];
                heap[writeIdx][1] = heap[i][1];
                writeIdx++;
            }
        }
        hsz = writeIdx;

        if (events[e][0][0] == 'O'){
            int uid = atoi(events[e][2]);
            online[uid] = false;
            heap[hsz][0] = time + 60;
            heap[hsz][1] = uid;
            hsz++;
        }else { // MESSAGE
        char* msg = events[e][2];
        char first = msg[0];

        if (first == 'A') { // "ALL"
            for (int j = 0; j < numberOfUsers; j++)
                ans[j]++;
        } else if (first == 'H') { // "HERE"
            for (int j = 0; j < numberOfUsers; j++)
                if (online[j])
                    ans[j]++;
        } else { // "id..."
            // Parse without strtok (avoid internal state)
            char* p = msg;
            while (*p) {
                if (p[0] == 'i' && p[1] == 'd') {
                    ans[atoi(p + 2)]++;
                    while (*p && *p != ' ')
                        p++;
                } else {
                    p++;
                }
            }
        }
    }
       
    }
    

    free(online);
    *returnSize = numberOfUsers;
    return ans;
}
