#include <string>
#include <iostream>
#include <list>
#include <algorithm>
#include <utility>
#include <iterator>
#include <set>
#include <unordered_set>
/*
在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表1->2->3->3->4->4->5 处理后为 1->2->5
*/
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution_by_direct_delete {
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

/*
在遍历单链表的时候，设置前节点与当前节点，检查当前节点与下一节点是否为相同值。
如果相同，继续查找至不同值的下一节点，然后指针改变指向，前节点连接至下一不同节点。
须注意，相同节点须删除内存。TODO状态。
*/
class Solution_by_direct_delete_simple {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode *header = new ListNode(0);
        header->next = pHead;
        if(pHead == NULL) return NULL;
        ListNode *prev = header;
        ListNode *curr = pHead;
        while(curr) {
            if (curr->next && curr->val == curr->next->val) {
                while(curr->next && curr->val == curr->next->val) {
                    curr = curr->next;
                }
                //TODO
                //delete node between prev and curr->next, NOT include prev&curr->next
                curr = curr->next;
                prev->next = curr;
            } else {
                prev = curr;
                curr = curr->next;
            }
        }

        ListNode *p = header->next;
        delete header;
        return p;
    }
};

/*
使用set，暴力解法。
显然如果能够知道重复的值是什么，然后再遍历一次单链表，删除重复值即可。
*/
class Solution_by_set {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
        ListNode *lt = pHead;
        ListNode *header = new ListNode(0);
        header->next = pHead;
        if(pHead == NULL) return NULL;

        //find repeated nodes, insert in set
        std::set<int> st;
        while(lt && lt->next) {
            if(lt->val == lt->next->val) {
                st.insert(lt->val);
            }
            lt = lt->next;
        }
        //traverse, delete found nodes
        lt = pHead;
        ListNode *prev = header;
        ListNode *tmp = NULL;
        while(lt) {
            if(st.find(lt->val) != st.end()) {
                tmp = lt;
                prev->next = lt->next;
                delete tmp;
                lt = prev->next;
            } else {
                lt = lt->next;
                prev = prev->next;
            }
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

    Solution_by_direct_delete *s = new Solution_by_direct_delete();
    ListNode *p = s->deleteDuplication(header);
    std::cout<<"after deleting duplications by direct delete, header is "<<p<<"\n";
    delete s;

    Solution_by_direct_delete_simple *s_simple = new Solution_by_direct_delete_simple();
    p = s_simple->deleteDuplication(header);
    std::cout<<"after deleting duplications by simple direct delete, header is "<<p<<"\n";
    delete s_simple;

    Solution_by_set *st = new Solution_by_set();
    p = st->deleteDuplication(header);
    std::cout<<"after deleting duplications by set, header is "<<p<<"\n";
    delete st;

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
