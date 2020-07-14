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
使用遍历。暴力解法。
*/
class Solution_by_compare {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1 || !pHead2) return NULL;
        ListNode *lt1 = pHead1;
        ListNode *lt2 = pHead2;
        ListNode *foundnode = NULL;
        while(lt1 != NULL) {
            lt2 = pHead2;
            while(lt2 != NULL) {
                if(lt1 == lt2) {
                    std::cout<<"found common node in list: "<<lt1<<"\n";
                    foundnode = lt1;
                    break;
                }
                if(foundnode) break;
                lt2 = lt2->next;
            }
            lt1 = lt1->next;
        }

        return foundnode;
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

/*
链接：https://www.nowcoder.com/questionTerminal/6ab1d9a29e88450685099d45c9e31e46?answerType=1&f=discussion
来源：牛客网

思路：首先我们要知道什么是公共节点，两个链表从某一节点开始，他们的next都指向同一个节点。
但由于是单向链表的节点，每个节点只有一个next，因此从第一个公共节点开始，之后他们的所有节点都是重合的，不可能再出现分叉。
所以可以先遍历两个链表得到他们的长度，就能知道哪个链表比较长，以及长的链表比短的链表多几个结点。
在第二次遍历的时候，在较长的链表上先走若干步，接着同时在两个链表上遍历，找到的第一个相同的结点就是他们的第一个公共结点。
*/
class Solution_by_fast_slow_runners {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1 || !pHead2) return NULL;
        ListNode *lt1 = pHead1;
        ListNode *lt2 = pHead2;
        ListNode *foundnode = NULL;
        int size1 = 0;
        int size2 = 0;
        //for non-loop list
        while(lt1) {
            lt1 = lt1->next;
            size1++;
            if(lt1 == pHead1) break;
        }
        while(lt2) {
            lt2 = lt2->next;
            size2++;
            if(lt2 == pHead2) break;
        }
        int diff = size1 > size2 ? size1 - size2 : size2 - size1;
        lt1 = pHead1;
        lt2 = pHead2;
        if (size1 > size2) {
            while(diff-- > 0) { lt1 = lt1->next;}
        } else {
            while(diff-- > 0) { lt2 = lt2->next;}
        }
        while(lt1 != lt2) {
            lt1 = lt1->next;
            lt2 = lt2->next;
        }
        foundnode = lt1;
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
    std::cout<<"found common node in list by set: "<<p<<"\n";
    delete st;

    Solution_by_compare *sc = new Solution_by_compare();
    p = sc->FindFirstCommonNode(header1, header2);
    std::cout<<"found common node in list by comparision: "<<p<<"\n";
    delete sc;
 
    Solution_by_fast_slow_runners *sr = new Solution_by_fast_slow_runners();
    p = sr->FindFirstCommonNode(header1, header2);
    std::cout<<"found common node in list by fast and slow runners: "<<p<<"\n";
    delete sr;
 
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
