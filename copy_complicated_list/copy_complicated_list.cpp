#include <iostream>
#include <list>
#include <algorithm>
#include <map>

/*
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针random指向一个随机节点），请对此链表进行深拷贝，并返回拷贝后的头结点。
*/

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};

/*
* 
*/
class Solution_by_map {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        //check
        if(pHead == NULL) return NULL;
        RandomListNode *lt, *ln;
        std::map<RandomListNode*, RandomListNode*> old2new;
        lt = pHead;
        //add new node in map<oldnode, newnode>
        while(lt) {
            ln = new RandomListNode(lt->label);
            old2new.insert(std::pair<RandomListNode*, RandomListNode*>(lt, ln));
            lt = lt->next;
        }
        //reconstruct new list.
        lt = pHead;
        //ln = old2new[lt];
        while(lt) {
            ln = old2new[lt];
            ln->next = old2new[lt->next];
            ln->random = old2new[lt->random];
            ln = ln->next;
            lt = lt->next;
        }
        //return newhead
        return old2new[pHead];
    }
};

/*
* Reconstruct list method.
*/
class Solution_by_reconstruct_list {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        //check
        if(pHead == NULL) return NULL;
        RandomListNode *newhead, *lt, *ln;
        lt = pHead;
        while(lt) {
            ln = new RandomListNode(lt->label);
            //lt = insertAsNext(lt, ln);//lt is the origin lt->next
            ln->next = lt->next;
            lt->next = ln;
            lt = ln->next ? ln->next : NULL;
        }
        lt = pHead;
        ln = pHead->next;
        //if ln->next true, ln->next->next true too.
        while(ln) {
            ln->random = lt->random ? lt->random->next : NULL;
            lt = ln->next ? ln->next : NULL;
            ln = ln->next ? ln->next->next : NULL;
        }
        //extract two lists
        lt = pHead;
        newhead = ln = pHead->next;
        while(ln) {
            lt->next = ln->next;
            ln->next = ln->next ? ln->next->next : NULL;
            lt = ln->next ? lt->next : NULL;
            ln = ln->next ? ln->next : NULL;
        }

        return newhead;
    }
};

void traverse(RandomListNode* lt)
{
    int i = 0;
    while(lt) {
        std::cout<<"["<<i<<"] node: "<<lt<<" random: "<<lt->random<<
        " lable: "<<lt->label<<";\n";
        lt = lt->next;
        i++;
    }
    std::cout<<"\n";
}

RandomListNode* constructList(int n, int arr[])
{
    RandomListNode *lt = NULL;
    RandomListNode *header = NULL;
    //construct list
    lt = header = new RandomListNode(arr[0]);
    int i = 1;
    while(n-- > 1) {
        lt->next = new RandomListNode(arr[i]);
        i++;
        lt = lt->next;
    }
    lt = header;
    while(lt->next->next) {
        lt->random = lt->next->next;
        lt = lt->next;
    }
    return header;
}

void deleteList(RandomListNode *header)
{
    //delete list
    RandomListNode *tmp;
    RandomListNode *lt = header;
    while(lt) {
        tmp = lt;
        lt = lt->next;
        delete tmp;
    }
}

int main()
{
    int arr[5] = {1, 2, 3, 4, 5};
    RandomListNode *header = constructList(5, arr);

    Solution_by_reconstruct_list *sr = new Solution_by_reconstruct_list();
    RandomListNode *p = sr->Clone(header);
    std::cout<<"origin list: "<<"\n";
    traverse(header);
    std::cout<<"copied list by reconstruction method: "<<"\n";
    traverse(p);
    delete sr;

    Solution_by_map *st = new Solution_by_map();
    p = st->Clone(header);
    std::cout<<"origin list: "<<"\n";
    traverse(header);
    std::cout<<"copied list by map method: "<<"\n";
    traverse(p);
    delete st;

    deleteList(header);
    return 0;
}
