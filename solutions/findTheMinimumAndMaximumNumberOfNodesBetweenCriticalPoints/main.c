#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

 

int* nodesBetweenCriticalPoints(struct ListNode* head, int* returnSize) {
    *returnSize = 2;
    int* ret = (int*)malloc(sizeof(int) * 2);
    ret[0] = ret[1] = -1;

    // Validação
    if (!head || !head->next || !head->next->next) {
        return ret;
    }

    int minDist = INT_MAX;
    int firstCritical = -1;
    int lastCritical = -1;
    int position = 1;

    struct ListNode* prev = head;
    struct ListNode* curr = head->next;

    while (curr->next) {
        int next_val = curr->next->val;
 
        if ((curr->val < prev->val && curr->val < next_val) ||
            (curr->val > prev->val && curr->val > next_val)) {
            
            if (firstCritical == -1) {
                firstCritical = position;
            } else {
                int dist = position - lastCritical;
                if (dist < minDist) {
                    minDist = dist;
                }
            }
            lastCritical = position;
        }

        prev = curr;
        curr = curr->next;
        position++;
    }
 
    if (firstCritical == -1 || firstCritical == lastCritical) {
        return ret;
    }

    ret[0] = minDist;
    ret[1] = lastCritical - firstCritical;

    return ret;
}