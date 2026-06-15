struct ListNode* deleteMiddle(struct ListNode* head) {
   
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    
    struct ListNode* slow = head;
    struct ListNode* fast = head->next->next;  
    
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    slow->next = slow->next->next;
    
    return head;
}
