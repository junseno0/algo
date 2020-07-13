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

class Solution {
public:
    ListNode* searchDiffNode(ListNode* startNode){
        if(startNode == NULL) return NULL;
        int val = startNode->val;
        ListNode *lt=startNode->next;
        while(lt && lt->val == val) {
            lt = lt->next;
        }
        return lt;
    }
    void deleteRepeatedNode(ListNode* prev, ListNode* next) {
        if(prev == NULL) return;
        ListNode *lt = prev->next;
        while(lt && lt != next) {
            ListNode* tmp = lt;
            lt = lt->next;
            delete tmp;
        }
    }
    
    ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode *lt = pHead;
        ListNode *header = new ListNode(0);
        header->next = pHead;
        ListNode *prev = header;
        ListNode *next = NULL;
        //check list
        if(!pHead) return NULL;
        
        //if delete repeated nodes in middle, link prev to next node
        while(lt && lt->next) {
            //find repeated nodes, store the node and its val
            while(lt->next && lt->val != lt->next->val) {
                //prev updated only when current node != next node
                //prev always ahead of current node
                prev = lt;
                lt = lt->next;
            }
            //if at last, break. boundary case.
            if(lt->next == NULL) {
                //prev = lt;
                break;
            }
            //search next diff node, set prev node and next node
            next = searchDiffNode(lt);
            //delete repeated nodes and link prev node and next node
            deleteRepeatedNode(prev, next);
            //link
            prev->next = next;
            //update lt
            lt = next;
        }
        
        //if repeated nodes in tail, prev node as tail node
        ListNode *p = header->next;
        delete header;
        return p;
    }
};

int main()
{
    int n = 7;
    ListNode *lt = NULL;
    ListNode *header = NULL;
    //construct list
    {
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
    }


    //find entry node
    Solution *s = new Solution();
    ListNode *p = s->deleteDuplication(header);
    std::cout<<"after deleting duplications, header is "<<p<<"\n";
    delete s;

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
