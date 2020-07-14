#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <iterator>
#include <set>
#include <unordered_set>
/*
输入两个链表，找出它们的第一个公共结点。
*/
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

/*
使用set。
*/
class Solution_by_set {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1 || !pHead2) return NULL;
        std::set<ListNode*> st;
        ListNode *lt = pHead1;
        ListNode *foundnode = NULL;
        while(lt) {
            st.insert(lt);
            lt = lt->next;
        }
        lt = pHead2;
        while(lt) {
            if(st.count(lt)) {
                std::cout<<"found common node in list: "<<lt<<"\n ";
                foundnode = lt;
                break;
            } else {
                lt = lt->next;
            }
        }
        return foundnode;
    }
};

int main()
{
    int n = 7;
    ListNode *lt = NULL;
    ListNode *header1 = NULL;
    ListNode *header2 = NULL;
    //construct list
    {
        lt = header1 = new ListNode(1);
        lt->next = new ListNode(2);
        lt = lt->next;
        lt->next = new ListNode(3);
        lt = lt->next;
        header2 = lt->next = new ListNode(4);
        std::cout<<"common node in list: "<<header2<<"\n";
        lt = lt->next;
        lt->next = new ListNode(5);
        lt = lt->next;
        lt->next = new ListNode(6);
        lt = lt->next;
        lt->next = new ListNode(7);
    }

    Solution_by_set *st = new Solution_by_set();
    ListNode *p = st->FindFirstCommonNode(header1, header2);
    std::cout<<"found common node in list: "<<p<<"\n";
    delete st;

    //delete list
    lt = header1;
    ListNode *tmp;
    for(int i = 0; i < n; i++) {
        tmp = lt;
        lt = lt->next;
        delete tmp;
    }
    return 0;
}
