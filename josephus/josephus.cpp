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
        while(boys->size() > 1) {
            int loopnum = m - 1;
            std::cout<<"lt: "<<lt<<" size: "<<boys->size()<<" data: "<<lt->data<<"\n";
            while(loopnum > 0) {
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

int main()
{
    Solution *s = new Solution();
    s->LastRemaining_Solution(5, 3);
    s->LastRemaining_Solution(0, 0);
    delete s;
    return 0;
}
