#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <iterator>
#include <set>
#include <unordered_set>
/*
给一个链表，若其中包含环，请找出该链表的环的入口结点，否则，输出null。
*/
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

/*
simple principle: A(start pos) --> B(entry pos) --> C(meeting pos) --> D(fast pos when slow arrives at B) --> B
X： A --> B
Y:　B --> C
u know: B --> C == D --> B
when meeting, slow ruuner runs X+Y, fast runner runs 2X+2Y, which equals X + Y + CDB + Y, so CDB = X.
*/
class Solution_two_runner {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        //check
        if (pHead == NULL) return NULL;
        ListNode *fast, *slow;
        fast = slow = pHead;
        int k = 0;
        do {
            if(fast->next == NULL || fast->next->next == NULL) return NULL;
            slow = slow->next;
            fast = fast->next->next;
        }while(fast != slow);
        slow = pHead;
        while(fast != slow) {
            fast = fast->next;
            slow = slow->next;
            k++;
        }
        std::cout<<"find entry node data: "<<slow->val<<"\n";
        return slow;
    }
};

class Solution_by_set {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        //check
        if (pHead == NULL) return NULL;
        std::pair<std::set<ListNode*>::iterator, bool> ret;
        std::set<ListNode*> nodeset;
        ListNode *lt = pHead;
        while(lt) {
            ret = nodeset.insert(lt);
            if(ret.second == false) return lt;
            lt = lt->next;
        }
        return NULL;
    }
};

//refer to https://www.nowcoder.com/questionTerminal/253d2c59ec3e4bc68da16833f79a38e4?answerType=1&f=discussion
class Solution_by_unordered_set {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
        std::unordered_set<ListNode*> st;
        while (pHead) {
            if (st.find(pHead) == st.end()) {
                st.insert(pHead);
                pHead = pHead->next;
            }
            else {
                return pHead;
            }
        }
        return NULL;
    }
};

int main()
{
    int n = 6;
    ListNode *lt = NULL;
    ListNode *header = NULL;
    //construct list
    for(int i = 0; i < n; i++) {
        if(!header) {
            header = lt = new ListNode(i);
        } else {
            lt->next = new ListNode(i);
            lt = lt->next;
        }
    }
    lt->next = header->next->next;    //entry node: 3th node
    std::cout<<"entry node data: "<<header->next->next->val<<"\n";

    //find entry node
    Solution_two_runner *s = new Solution_two_runner();
    s->EntryNodeOfLoop(header);
    delete s;

    Solution_by_set *st = new Solution_by_set();
    ListNode *valnode = st->EntryNodeOfLoop(header);
    std::cout<<"find entry node dat by set: "<<valnode->val<<"\n";
    delete st;

    Solution_by_unordered_set *sut = new Solution_by_unordered_set();
    valnode = sut->EntryNodeOfLoop(header);
    std::cout<<"find entry node dat by set: "<<valnode->val<<"\n";
    delete sut;

    //delete list
    lt = header;
    ListNode *tmp;
    for(int i = 0; i < n; i++) {
        tmp = lt;
        lt = lt->next;
        delete tmp;
    }
    return 0;
}
