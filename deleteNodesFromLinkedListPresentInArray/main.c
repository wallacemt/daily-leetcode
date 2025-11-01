struct ListNode* modifiedList(int* nums, int numsSize, struct ListNode* head) {
    int maxVal = 100000;
    bool* toRemove = (bool*)calloc(maxVal + 1, sizeof(bool));
    
    for (int i = 0; i < numsSize; i++) {
        toRemove[nums[i]] = true;
    }

    struct ListNode dummy;
    dummy.next = head;
    struct ListNode* prev = &dummy;
    struct ListNode* curr = head;
    
    while (curr != NULL) {
        if (toRemove[curr->val]) {
            prev->next = curr->next;
            struct ListNode* temp = curr;
            curr = curr->next;
            free(temp);
        } else {
            prev = curr;
            curr = curr->next;
        }
    }
    
    free(toRemove);
    return dummy.next;
}
