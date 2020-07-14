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

/*
链接：https://www.nowcoder.com/questionTerminal/6ab1d9a29e88450685099d45c9e31e46?answerType=1&f=discussion
来源：牛客网

双指针法。创建两个指针p1和p2,分别指向两个链表的头结点，然后依次往后遍历。
如果某个指针到达末尾，则将该指针指向另一个链表的头结点；如果两个指针所指的节点相同，则循环结束，返回当前指针指向的节点。
比如两个链表分别为：1->3->4->5->6和2->7->8->9->5->6。短链表的指针p1会先到达尾部，然后重新指向长链表头部，
当长链表的指针p2到达尾部时，重新指向短链表头部，此时p1在长链表中已经多走了k步(k为两个链表的长度差值)，
p1和p2位于同一起跑线，往后遍历找到相同节点即可。其实该方法主要就是用链表循环的方式替代了长链表指针先走k步这一步骤。
*/
class Solution_by_two_pointers {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        if(!pHead1 || !pHead2) return NULL;
        ListNode *lt1 = pHead1;
        ListNode *lt2 = pHead2;
        ListNode *foundnode = NULL;
        bool lt1pass = false;//if none same nodes, at last lt1 == lt2 == NULL. to remove it.
        bool lt2pass = false;
        while(lt1 != lt2) {
            lt1 = lt1->next;
            if(lt1pass && lt1 == NULL) break;
            if(lt1 == NULL) {
                lt1 = pHead2;
                lt1pass = true;
            }
            //if lt1 pass list2, then no common node
            lt2 = lt2->next;
            if(lt2pass && lt2 == NULL) break;
            if(lt2 == NULL) {
                lt2 = pHead1;
                lt2pass = true;
            }
            //if lt1 pass list2, then no common node
        }
        if(lt1 == lt2) foundnode = lt1;
        return foundnode;
    }
};

class Solution_by_two_pointers_nk {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode *ta = pHead1, *tb = pHead2;
        while (ta != tb) {
            ta = ta ? ta->next : pHead2;
            tb = tb ? tb->next : pHead1;
        }
        return ta;
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

    Solution_by_two_pointers *ss = new Solution_by_two_pointers();
    p = ss->FindFirstCommonNode(header1, header2);
    std::cout<<"found common node in list by two pointers: "<<p<<"\n";
    delete ss;

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
