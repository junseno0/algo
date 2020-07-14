#include <iostream>
#include <list>
#include <algorithm>
#include <stack>

/*
输入一个链表，输出该链表中倒数第k个结点。
*/
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

/*
使用两次循环遍历。
*/
class Solution_by_loop_traverse {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        //check
        if (!pListHead || k < 1) return nullptr;
        //a runner run to end of list, with sz step, then keep run sz - k step from beginning.
        //when runner stops, the position is the target.
        ListNode *lt = pListHead;
        int sz = 0;
        int targetstep = 0;
        while(lt != NULL) {
            lt = lt->next;
            sz++;
        }
        targetstep = sz - k;
        if (targetstep < 0) return NULL;
        lt = pListHead;
        while(targetstep > 0) {
            lt = lt->next;
            targetstep--;
        }
        return lt;
    }
};

/*
使用快慢指针。
*/
class Solution_by_two_runners {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        //CHECK
        if (!pListHead || k < 1) return NULL;
        //two runners, diff k step, fast runner at the end while slow runner at last K node
        ListNode *fast, *slow;
        fast = slow = pListHead;
        int n = k - 1;
        while(n) {
            fast = fast->next;
            n--;
            if(!fast) return NULL;
        }
        while(fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        //return K node
        return slow;
    }
};

/*
Reverse list and run k step. TODO.
*/
class Solution_by_reverse {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        return NULL;
    }
};

/*
Recursion. TODO.
*/
class Solution_by_recursion {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        return NULL;
    }
};

void traverse(ListNode* lt)
{
    int i = 0;
    while(lt) {
        std::cout<<"["<<i<<"] node: "<<lt<<" val: "<<lt->val<<";\n";
        lt = lt->next;
        i++;
    }
    std::cout<<"\n";
}

ListNode* constructList(int n)
{
    ListNode *lt = NULL;
    ListNode *header = NULL;
    //construct list
    lt = header = new ListNode(1);
    lt->next = new ListNode(2);
    lt = lt->next;
    lt->next = new ListNode(3);
    lt = lt->next;
    lt->next = new ListNode(4);
    lt = lt->next;
    lt->next = new ListNode(5);
    lt = lt->next;
    lt->next = new ListNode(6);
    lt = lt->next;
    lt->next = new ListNode(7);
    return header;
}

void deleteList(ListNode *header, int n)
{
    //delete list
    ListNode *tmp;
    ListNode *lt = header;
    for(int i = 0; i < n; i++) {
        tmp = lt;
        lt = lt->next;
        delete tmp;
    }
}

int main()
{
    int n = 7;
    ListNode *header = constructList(n);

    Solution_by_two_runners *sr = new Solution_by_two_runners();
    ListNode *p = sr->FindKthToTail(header, 2);
    traverse(header);
    delete sr;

    Solution_by_loop_traverse *sl = new Solution_by_loop_traverse();
    p = sl->FindKthToTail(header, 2);
    traverse(header);
    delete sl;

    deleteList(header, n);
    return 0;
}
