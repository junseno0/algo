#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <stack>
/*
输入一个链表，按链表从尾到头的顺序返回一个ArrayList。
*/
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

/*
* Recursion method.
*/
class Solution_by_recursion {
public:
    void ListFromTailToHead(ListNode* head, std::vector<int> &vt) {
        if(head == NULL) return;
        ListFromTailToHead(head->next, vt);
        vt.push_back(head->val);
        return;
    }
    std::vector<int> printListFromTailToHead(ListNode* head) {
        //recursion method
        std::vector<int> vt;
        //check
        if(head == NULL) return vt;
        //recursion method
        ListFromTailToHead(head, vt);
        return vt;
    }
};

/*
* Recursion method with 1 input para. TODO.
*/
class Solution_by_recursion_v2 {
public:
    std::vector<int> printListFromTailToHead(ListNode* head) {
        //recursion method
        std::vector<int> vt;
        //check
        if(head == NULL) return vt;
        //recursion method
        //TODO
        return vt;
    }
};

/*
* Stack method.
*/
class Solution_by_stack {
public:
    std::vector<int> printListFromTailToHead(ListNode* head) {
        //recursion method
        std::vector<int> vt;
        //check
        if(head == NULL) return vt;
        std::stack<int> st;
        ListNode* lt = head;
        while(lt) {
            st.push(lt->val);
            lt = lt->next;
        }
        while(!st.empty()) {
            vt.push_back(st.top());
            st.pop();
        }
        return vt;
    }
};

/*
* Reverse vector method.
*/
class Solution_by_reverse_vector {
public:
    std::vector<int> printListFromTailToHead(ListNode* head) {
        //recursion method
        std::vector<int> vt;
        //check
        if(head == NULL) return vt;
        ListNode* lt = head;
        while(lt) {
            vt.push_back(lt->val);
            lt = lt->next;
        }
        //reverse vector, possible STL:
        //template< class BidirIt >
        //void reverse( BidirIt first, BidirIt last );
        int n = vt.size();
        int i = 0;
        int j = n - 1;
        while(i < j) {
            std::swap(vt[i], vt[j]);
            ++i; --j;
        }
        return vt;
    }
};

/*
* Reverse list and push node val into vector.
*/
class Solution_by_reverse_list {
public:
    ListNode* reverseList(ListNode* head) {
        if(head == NULL) return NULL;
        // 2 pointers. prev, curr
        // store curr next one
        // curr runs/updates from head to end, relink all the way behind it
        //in the end, curr as null, prev as end of list
        ListNode* prev = NULL;
        ListNode* curr = head;
        ListNode* next = NULL;
        while(curr != NULL) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        //return node
        return prev;
    }
    std::vector<int> printListFromTailToHead(ListNode* head) {
        //recursion method
        std::vector<int> vt;
        //check
        if(head == NULL) return vt;
        ListNode *lt = head;
        lt = reverseList(lt);
        while(lt) {
            vt.push_back(lt->val);
            lt = lt->next;
        }
        return vt;
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

ListNode* constructList(int n, int arr[])
{
    ListNode *lt = NULL;
    ListNode *header = NULL;
    //construct list
    lt = header = new ListNode(arr[0]);
    int i = 1;
    while(n-- > 1) {
        lt->next = new ListNode(arr[i]);
        i++;
        lt = lt->next;
    }
    return header;
}

void deleteList(ListNode *header)
{
    //delete list
    ListNode *tmp;
    ListNode *lt = header;
    while(lt) {
        tmp = lt;
        lt = lt->next;
        delete tmp;
    }
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    ListNode *header = constructList(5, arr);

    Solution_by_recursion *sr = new Solution_by_recursion();
    std::vector<int> vt = sr->printListFromTailToHead(header);
    traverse(header);
    for(unsigned int i = 0; i < vt.size(); i++) {
        std::cout<<"["<<vt[i]<<"] ";
    }
    std::cout<<"\n";
    delete sr;

    Solution_by_stack *st = new Solution_by_stack();
    std::vector<int> vs = st->printListFromTailToHead(header);
    traverse(header);
    for(unsigned int i = 0; i < vs.size(); i++) {
        std::cout<<"["<<vs[i]<<"] ";
    }
    std::cout<<"\n";
    delete st;

    Solution_by_reverse_vector *sv = new Solution_by_reverse_vector();
    std::vector<int> vv = sv->printListFromTailToHead(header);
    traverse(header);
    for(unsigned int i = 0; i < vv.size(); i++) {
        std::cout<<"["<<vv[i]<<"] ";
    }
    std::cout<<"\n";
    delete sv;

    Solution_by_reverse_list *sl = new Solution_by_reverse_list();
    std::vector<int> vl = sl->printListFromTailToHead(header);
    traverse(header);//list itself is changed now!! u cannot delete it on heap now!!
    for(unsigned int i = 0; i < vl.size(); i++) {
        std::cout<<"["<<vl[i]<<"] ";
    }
    std::cout<<"\n";
    delete sl;//cannot delete all nodes now.

    deleteList(header);
    return 0;
}
