/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if (!head || !head->next)
        return head;
    
    int count = 1;
    struct ListNode *tail = head;
    
    while (tail->next) {
        tail = tail->next;
        count++;
    }
    
    // Normalizar k
    k %= count;
    if (k == 0)
        return head;
    
    struct ListNode *newTailPrev = head;
    for (int i = 0; i < count - k - 1; i++) {
        newTailPrev = newTailPrev->next;
    }
    
    struct ListNode *newHead = newTailPrev->next;
    newTailPrev->next = NULL;
    tail->next = head;
    
    return newHead;
}