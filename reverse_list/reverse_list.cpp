#include <iostream>
#include <list>
#include <algorithm>
#include <stack>

/*
输入一个链表，反转链表后，输出新链表的表头。
*/
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

/*
使用栈。
*/
class Solution_by_stack {
public:
    ListNode* ReverseList(ListNode* pHead) {
        //check
        if(!pHead) return NULL;
        std::stack<ListNode*> st;
        ListNode* lt = pHead;
        ListNode* newHeader = new ListNode(0);
        while(lt) {
            st.push(lt);
            lt = lt->next;
        }
        lt = newHeader;
        while(!st.empty()) {
            lt->next = st.top();
            lt = lt->next;
            st.pop();
        }
        //last node reset next pointer.
        lt->next = NULL;
        //find real new header
        lt = newHeader->next;
        delete newHeader;
        return lt;
    }
};

// 2 trick here. NOT enough simple.
class Solution_by_direct_traverse {
public:
    ListNode* ReverseList(ListNode* pHead) {
        //check
        if(!pHead) return NULL;
        //if(pHead->next == NULL) return pHead;
        ListNode* header = new ListNode(-2);
        ListNode* trailer = new ListNode(-1);
        header->next = pHead;
        ListNode *prev = header;
        ListNode *curr = pHead;
        ListNode *next = curr->next ? curr->next : trailer;//trick #1 here.
        //set trailer
        while(curr->next) {
            curr = curr->next;
        }
        curr->next = trailer;
        curr = pHead;
        
        //traverse and reverse nodes of prev and curr
        //then update curr to prev, next to curr, next-next to next
        //until next is trailer
        while(next != NULL) {
            if(curr != pHead) 
                curr->next = prev;
            else
                curr->next = NULL;//trick #2 here.
            prev = curr;
            curr = next;
            next = next->next;
        }

        //delete nodes
        delete header;
        delete trailer;
        
        return prev;
    }
};

/*
简洁的三指针解法，TODO
*/
class Solution_by_direct_traverse_simple {
public:
    ListNode* ReverseList(ListNode* pHead) {
        return NULL;
    }
};

class Solution_by_recursion{
    public:
    ListNode* reverse(ListNode* curr, ListNode* next) {
        if(next == NULL) return curr;
        ListNode* nnext = next->next;
        next->next = curr;
        curr = next;
        return reverse(curr, nnext);
    }
    ListNode* ReverseList(ListNode* pHead) {
        if(pHead == NULL) return NULL;
        if(pHead->next == NULL) return pHead;
        return reverse(NULL, pHead);//trick here. first node next = NULL
    }
};

/*
递归实现/solution by recursion
Image playing mahjong, when you try to reverse the n cards, reverse n-1 cards firstly.
You should always return the new header.
But the n card should stick to the correct card's next position.\
mahjong cards:
1-2-3-4-5
......
1 5-4-3-2
5-4-3-2-1
*/
class Solution_by_recursion_v2{
    public:
    ListNode* ReverseList(ListNode* pHead) {
        if(NULL == pHead) return NULL;
        if(NULL == pHead->next) return pHead;
        ListNode* header = ReverseList(pHead->next);
        pHead->next->next = pHead;//trick here.
        pHead->next = NULL;
        return header;
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

    Solution_by_stack *st = new Solution_by_stack();
    header = st->ReverseList(header);
    traverse(header);
    delete st;

    Solution_by_direct_traverse *sr = new Solution_by_direct_traverse();
    header = sr->ReverseList(header);
    traverse(header);
    delete sr;

    Solution_by_recursion *ss = new Solution_by_recursion();
    header = ss->ReverseList(header);
    traverse(header);
    delete ss;

    Solution_by_recursion_v2 *ss2 = new Solution_by_recursion_v2();
    header = ss2->ReverseList(header);
    traverse(header);
    delete ss2;

    deleteList(header, n);
    return 0;
}
