/*
孩子们的游戏(圆圈中最后剩下的数)
每年六一儿童节,牛客都会准备一些小礼物去看望孤儿院的小朋友,今年亦是如此。
HF作为牛客的资深元老,自然也准备了一些小游戏。其中,有个游戏是这样的:
首先,让小朋友们围成一个大圈。然后,他随机指定一个数m,让编号为0的小朋友开始报数。
每次喊到m-1的那个小朋友要出列唱首歌,然后可以在礼品箱中任意的挑选礼物,
并且不再回到圈中,从他的下一个小朋友开始,继续0...m-1报数....这样下去....直到
剩下最后一个小朋友,可以不用表演,并且拿到牛客名贵的“名侦探柯南”典藏版(名额有限哦!!^_^)。
请你试着想下,哪个小朋友会得到这份礼品呢？(注：小朋友的编号是从0到n-1)

如果没有小朋友，请返回-1
*/
#include <string>
#include <iostream>
#include <list>
#include <algorithm>

namespace Bob{
//define node list with prev and next, data(int)
//define construct method with n
//define size method
//define remove method, return type : next node, update it as header
template <typename T> struct ListNode{
    T data;
    ListNode<T> *prev;
    ListNode<T> *next;
};
template <typename T> class List{
    int _size;
    public:
    ListNode<T> *header;
    List();
    List(int n);
    ~List();
    ListNode<T>* remove(ListNode<T>* lt);
    void traverse();
    int size(){return _size;};
};

template <typename T> List<T>::List(){
    _size = 0;
    header = NULL;
}
    
template <typename T> List<T>::List(int n) {
    if (n < 1) return;
    _size = n;
    ListNode<T> *lt = NULL;
    ListNode<T> *prev = NULL;
    ListNode<T> *first = NULL;
    for(int i = 0; i < n; i++) {
        lt = new ListNode<T>;
        if(!first) first = lt;
        if (prev) prev->next = lt;
        lt->prev = prev;
        lt->next = NULL;
        prev = lt;
        lt->data = i;
    }
    lt->next = first;
    first->prev = lt;
    header = first;
}
    
template <typename T> List<T>::~List() {
    ListNode<T> *lt = header;
    int n = size();
    ListNode<T> *nextnode;
    while(n-- > 0) {
        nextnode = lt->next;
        delete lt;
        lt = nextnode;
    }
}
    
template <typename T> ListNode<T>* List<T>::remove(ListNode<T>* lt) {
    ListNode<T> *nextnode;
    lt->prev->next = lt->next;
    lt->next->prev = lt->prev;
    nextnode = lt->next;
    delete lt;
    header = nextnode;
    _size--;
    return nextnode;
}

template <typename T> void List<T>::traverse(){
    int n = size();
    ListNode<T> *lt = header;
    while(n > 0) {
        std::cout<<"["<<n<<"] "<<lt->data<<"  ";
        lt = lt->next;
        n--;
    }
    std::cout<<"\n";
}

}

using namespace Bob;
class Solution {
public:
    int LastRemaining_Solution(int n, int m)
    {
        ListNode<int> *lt;
        //check n and m
        if (n < 1 || m < 1) return -1;
        //return if only one node and two node
        if (n == 1) return 1;
        if (n == 2) return m % 2 ? 1 : 2;
        
        //construct a list with n nodes
        List<int> *boys = new List<int>(n);
        lt = boys->header;
        std::cout<<"n: "<<n<<" m: "<<m<<"\n";
        //while size > 1, move m nodes and remove the target node
        //It is hard to determine loop num
        //For example, 6 kids, m = 5, the 5-th kid out. move 5-1 step from header
        //6 kids, m = 6, the 6-th kid out, move 6-1 step from header
        //6 kids, m = 7, the 7-6= 1 th kid out, mvoe 1-1 step from header
        while(boys->size() > 1) {
            //if m = size, remove the last one
            //if m % size = 0 && m > size, remove the last one
            int loopnum = m;
            if(m > boys->size()) loopnum = m % boys->size();
            if (loopnum == 0) loopnum = boys->size();
            std::cout<<"lt: "<<lt<<" size: "<<boys->size()<<" data: "<<lt->data<<"\n";
            while(loopnum > 1) {
                if (!lt->next) std::cout<<"NULL lt->next!!!!"<<"\n";
                std::cout<<"lt next: "<<lt->next<<"\n";
                lt = lt->next;
                loopnum--;
            }
            lt = boys->remove(lt);//returned lt is next node
            boys->traverse();
        }
        
        int val = lt->data;
        std::cout<<"val: "<<val<<"\n";
        delete boys;
        //return data/number when only one node
        return val;
    }
};

class Solution_stl {
public:
    int LastRemaining_Solution(int n, int m)
    {
        //check n and m
        if (n < 1 || m < 1) return -1;
        //return if only one node and two node
        if (n == 1) return 1;
        if (n == 2) return m % 2 ? 1 : 2;

        //construct a list with n nodes
        std::list<int> boys;
        for(int i = 0; i < n; i++) boys.push_back(i);
        for(std::list<int>::iterator it = boys.begin(); it != boys.end(); it++)
            std::cout<<*it<<" ";
        std::cout<<"\n";
        std::list<int>::iterator lt = boys.begin();
        while(boys.size() > 1) {
            //if m = size, remove the last one
            //if m % size = 0 && m > size, remove the last one
            int loopnum = m;
            while(loopnum > 1) {
                if (++lt == boys.end()) {
                    lt = boys.begin();
                } else {
                    //lt++; //increase in if statement
                }
                loopnum--;
            }
            lt = boys.erase(lt);
            if(lt == boys.end()) {
                lt = boys.begin();
            }

        }
        int val = *lt;
        //return data/number when only one node
        return val;
    }
};

class Solution_stl_nk {
public:
    int LastRemaining_Solution(int n, int m)
    {
        if (n <= 0) return -1;
        std::list<int> lt;
        for (int i=0; i<n; ++i)
            lt.push_back(i);
        int index = 0;
        while (n > 1) {
            index = (index + m - 1) % n;//math induction
            std::list<int>::iterator it = lt.begin();
            std::advance(it, index);//std::advance, see also std::prev, next, distance
            lt.erase(it);
            --n;
            for(std::list<int>::iterator i = lt.begin(); i != lt.end(); i++)
                std::cout<<*i<<" ";
            std::cout<<"\n";
        }
        std::cout<<"lt front: "<<lt.front()<<" lt back: "<<lt.back()<<"\n";
        return lt.back();
    }
};

/*
Formulas deviration: refer to https://blog.csdn.net/SCS199411/article/details/92988332
*/
class Solution_recursion {
public:
    int LastRemaining_Solution(int n, int m)
    {
        if (n <= 0) return -1;
        if (n == 1) return  0;
        return (LastRemaining_Solution(n-1, m) + m) % n;

    }
};

class Solution_iteration {
public:
    int LastRemaining_Solution(int n, int m)
    {
        if (n <= 0) return -1;
        if (n == 1) return  0;
        int val = 0;
        int iter = 2;
        while(iter <= n) {
            val = (val + m) % iter;
            iter++;
        }
        return val;
    }
};

int main()
{
    int val = 0;
    Solution *s = new Solution();
    s->LastRemaining_Solution(5, 3);
    s->LastRemaining_Solution(0, 0);
    s->LastRemaining_Solution(6, 6);
    delete s;

    Solution_stl *sl = new Solution_stl();
    val = sl->LastRemaining_Solution(5, 3);
    std::cout<<"sl->LastRemaining_Solution(5, 3): "<<val<<"\n";
    val = sl->LastRemaining_Solution(0, 0);
    val = sl->LastRemaining_Solution(6, 6);
    std::cout<<"sl->LastRemaining_Solution(6, 6): "<<val<<"\n";
    delete sl;

    Solution_stl_nk *sl_nk = new Solution_stl_nk();
    val = sl_nk->LastRemaining_Solution(5, 3);
    std::cout<<"sl_nk->LastRemaining_Solution(5, 3): "<<val<<"\n";
    val = sl_nk->LastRemaining_Solution(0, 0);
    val = sl_nk->LastRemaining_Solution(6, 6);
    std::cout<<"sl_nk->LastRemaining_Solution(6, 6): "<<val<<"\n";
    delete sl_nk;

    Solution_recursion *sl_re = new Solution_recursion();
    val = sl_re->LastRemaining_Solution(5, 3);
    std::cout<<"sl_nk->LastRemaining_Solution(5, 3): "<<val<<"\n";
    val = sl_re->LastRemaining_Solution(0, 0);
    val = sl_re->LastRemaining_Solution(6, 6);
    std::cout<<"sl_nk->LastRemaining_Solution(6, 6): "<<val<<"\n";
    delete sl_re;

    Solution_iteration *sl_iter = new Solution_iteration();
    val = sl_iter->LastRemaining_Solution(5, 3);
    std::cout<<"sl_nk->LastRemaining_Solution(5, 3): "<<val<<"\n";
    val = sl_iter->LastRemaining_Solution(0, 0);
    val = sl_iter->LastRemaining_Solution(6, 6);
    std::cout<<"sl_nk->LastRemaining_Solution(6, 6): "<<val<<"\n";
    delete sl_iter;

    return 0;
}
