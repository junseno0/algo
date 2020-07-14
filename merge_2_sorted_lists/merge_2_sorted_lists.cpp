#include <iostream>
#include <list>
#include <algorithm>
#include <stack>

/*
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
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
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if (!pHead1 || !pHead2) return pHead1 == nullptr ? pHead2: pHead1;
        ListNode* p;
        if (pHead1->val <= pHead2->val) {
            p = pHead1;
            pHead1 = pHead1->next;
        } else {
            p = pHead2;
            pHead2 = pHead2->next;
        }
        p->next = Merge(pHead1, pHead2);
        return p;
    }
};

/*
Reconstruct list.
一般创建单链表，都会设一个虚拟头结点，也叫哨兵，因为这样每一个结点都有一个前驱结点。TODO.
设置一个“哨兵节点”叫header，这会让代码写起来非常简单清爽，省了烧脑的边界条件。
*/
class Solution_by_reconstruction {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        //check
        if(!pHead1) return pHead2;
        if(!pHead2) return pHead1;
        ListNode *lt1 = pHead1;
        ListNode *lt2 = pHead2;
        ListNode *header = NULL;
        ListNode *lt = NULL;
        while(lt1 && lt2) {
            //if lt1 val < lt2 val , push lt1 to newlist
            //otherwise, push lt2 to newlist
            //until lt1 and lt2 are NULL.
            if(lt1->val < lt2->val) {
                if(!header) {
                    header = lt = lt1;
                    lt1 = lt1->next;
                } else {
                    lt->next = lt1;
                    lt = lt->next;
                    lt1 = lt1->next;
                }
            } else {
                if(!header) {
                    header = lt = lt2;
                    lt2 = lt2->next;
                } else {
                    lt->next = lt2;
                    lt = lt->next;
                    lt2 = lt2->next;
                }
            }
        }
        lt->next = lt1 ? lt1 : lt2;
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
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[3] = {3, 5, 7};
    ListNode *header1 = constructList(5, arr1);
    ListNode *header2 = constructList(3, arr2);

    Solution_by_reconstruction *sr = new Solution_by_reconstruction();
    ListNode *p = sr->Merge(header1, header2);
    traverse(p);
    delete sr;

    deleteList(p);

    ListNode *header3 = constructList(5, arr1);
    ListNode *header4 = constructList(3, arr2);
    Solution_by_recursion *se = new Solution_by_recursion();
    p = se->Merge(header3, header4);
    traverse(p);
    delete se;

    deleteList(p);
    return 0;
}
