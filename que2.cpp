class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (!head || !head->next) return true;
        
        ListNode* slow = head;
        ListNode* fast = head;
        while (fast->next && fast->next->next) {
            slow = slow->next;
            fast = fast->next->next;
        }

        ListNode* secondHalf = reverseList(slow->next);
        ListNode* firstHalf = head;
        ListNode* temp = secondHalf;
        bool isPalin = true;

        while (temp) {
            if (firstHalf->val != temp->val) {
                isPalin = false;
                break;
            }
            firstHalf = firstHalf->next;
            temp = temp->next;
        }

        slow->next = reverseList(secondHalf);
        return isPalin;
    }

private:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        while (head) {
            ListNode* nextNode = head->next;
            head->next = prev;
            prev = head;
            head = nextNode;
        }
        return prev;
    }
};
