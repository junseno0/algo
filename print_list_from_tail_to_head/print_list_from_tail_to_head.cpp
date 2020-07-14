#include <iostream>
#include <list>
#include <algorithm>
#include <vector>

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
Recursion method.
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
    delete sr;

    deleteList(header);
    return 0;
}
