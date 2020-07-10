#include <iostream>
#include <string>
using namespace std;
//template<typename T> typedef ListNode<T> ListNode<T>;
template <class T>
struct ListNode{
    //member data
    T data;
    ListNode<T> *prev;
    ListNode<T> *next;
    //construct func
    ListNode<T>(){}
    ListNode<T>(T e, ListNode<T> *prev = NULL, ListNode<T> *next = NULL):
        data(e), prev(prev), next(next){}
    //ops
    //insert a node of e as the prev of this node.
    ListNode<T>* insertAsPrev(T e) {
        ListNode<T> *xnode = new ListNode<T>(e, prev, this);
        //set prev-next before prev.
        prev->next = xnode;//for pre node, its next node is xnode
        prev = xnode;//for this node, pred node is xnode.
        return xnode;
        }
    //insert a node of e as the next of this node.
    ListNode<T>* insertAsSucc(T e) {
        ListNode<T> *xnode = new ListNode<T>(e, this, next);
        next->prev = xnode;
        next = xnode;
        return xnode;
        }
};

template <typename T> class List{
    int _size;//to init as 0
    ListNode<T> *header;
    ListNode<T> *trailer;
    protected:
    void init();
    void clear();
    public:
    //construct
    List(){init();};
    //copy construct
    List(List<T>* copylist);
    //deconstruct
    ~List();
    //insert
    ListNode<T>* insertAsFirst(T e);
    ListNode<T>* insertAsLast(T e);
    ListNode<T>* insertAsPrev(ListNode<T>* P, T e);
    ListNode<T>* insertAsSucc(ListNode<T>* p, T e);
    //remove one ListNode p
    T remove(ListNode<T>* p);
    //find
    ListNode<T>* find(T e);
    ListNode<T>* find(T e, int n, ListNode<T>* p);
    //In oreder list, find the last node whose data <= n
    ListNode<T>* search(T e, int n, ListNode<T>* p);
    //deduplicate
    int deduplicate();
    //uniquity
    void uniquity();
    //visit member by iterator
    void traverse();
    void traverse(void (*visit) (T&));
    template <typename VST> void traverse(VST& visit);
    //sort all with inserting sort
    void interationSort();
    //sort all with selection sort
    void selectionSort();
    void selectionSort_2(ListNode<T>* p, int n);
    //size
    int size(){return _size;}
};

template <typename T> void List<T>::init(){
    header = new ListNode<T>;
    trailer = new ListNode<T>;
    header->next = trailer;
    header->prev = NULL;
    trailer->next = NULL;
    trailer->prev = header;
    _size = 0;
}

template <typename T> List<T>::List(List<T>* copylist)
{
    //set header and trailer
    init();
    header->data = copylist->header->data;
    trailer->data = copylist->trailer->data;
    //new one by one
    ListNode<T> *ltnode = header;
    ListNode<T> *copynode = copylist->header->next;
    int size = copylist->size();
    while(size-- > 0){
        ltnode = insertAsSucc(ltnode, copynode->data);
        copynode = copynode->next;
    }
}

//return type: void
//return type: old size
template <typename T> void List<T>::clear()
{
    while(_size > 0){//_size would be updated after remove ops.
        remove(header->next);//header next would be updated after remove ops.
    }
}

template <typename T> List<T>::~List()
{
    clear();
    delete header;
    delete trailer;
}

template <typename T> ListNode<T>* List<T>::insertAsFirst(T e)
{
    _size++;
    return this->header->insertAsSucc(e);
}

template <typename T> ListNode<T>* List<T>::insertAsLast(T e)
{
    _size++;
    return this->trailer->insertAsPrev(e);
}

template <typename T> ListNode<T>* List<T>::insertAsPrev(ListNode<T>* p, T e)
{
    _size++;
    return p->insertAsPrev(e);
}

template <typename T> ListNode<T>* List<T>::insertAsSucc(ListNode<T>* p, T e)
{
    _size++;
    return p->insertAsSucc(e);
}

//return data, not ListNode
//it is simple when header and trailer are set
template <typename T> T List<T>::remove(ListNode<T>* p)
{
    //if no p in List??

    //p prev --> p next
    //p next prev : p prev next
    T e = p->data;
    p->next->prev = p->prev;
    p->prev->next = p->next;
    delete p;
    _size--;
    return e;
}

//return type: target node or null
//find the target node p in ahead n nodes.
template <typename T> ListNode<T>* List<T>::find(T e, int n, ListNode<T>* p)
{
    if(n >= this->size()) n = this->size();
    ListNode<T>* lt = header->next;
    while(n-- > 0){
        if(lt->data == p->data){
            return lt;
        }
        lt = lt->next;
    }
    return NULL;
}

template <typename T> ListNode<T>* List<T>::find(T e)
{
    ListNode<T>* p = this->header->next;
    int size = this->size();
    while(size-- > 0){
        if(p->data == e)
            return p;
        p = p->next;
    }
    return NULL;
}

template <typename T> ListNode<T>* List<T>::search(T e, int n, ListNode<T>* p)
{
    //p is the give node, search target node from node p.
    //p = trailer->prev;
    while(n-- >= 0){ // n = 0 means that the first node data is still greater than e
        if((p = p->prev)->data <= e) break;
    }
    return p;
}

template <typename T> int List<T>::deduplicate(){
    if(this->size() < 2) return 0;
    //iterator from header->next to trailer->prev
    //find same node before iterator and remove it
    //until trailer->prev
    //no same nodes from header->next to iterator.
    int size = 0;
    int oldsize = this->size();
    ListNode<T>* lt = header;
    while((lt = lt->next) != trailer){
        ListNode<T>* samenode = find(lt->data, size, lt);
        if(samenode)
            remove(samenode);
        else
            size++;//if one node removed, size indeed had decrease.
    }
    return oldsize - this->size();
}

/*
//return type: current size
//score: bad
template <typename T> int List<T>::deduplicate(){
    int size = this->size();
    //
    ListNode<T>* lt = header->next;
    ListNode<T>* lt_tmp;
    while(lt != trailer){
        lt_tmp = lt->next;
        int size_tmp = size--;
        while(size_tmp-- > 0){
            if(!(lt->data).compare(lt_tmp->data)){
                //if you remove one node, make sure store the next node.
                ListNode<T>* lt_stage = lt_tmp->next;
                remove(lt_tmp);
                size_tmp--;
                size--;//size indicates _size
                lt_tmp = lt_stage;
                continue;
            }
            lt_tmp = lt_tmp->next;
        }        
        lt = lt->next;
    }
    return size;//current size
}
*/

template <typename T> void List<T>::traverse()
{
    //visit member by iterator
    ListNode<T>* lt = this->header->next;
    int size = this->size();
    while(size--){
        std::cout<<"["<<this->size() - size <<"] " <<"node:"<<lt <<" data:"<< lt->data<<"  ";
        lt = lt->next;
    }
    std::cout<<std::endl;
}

template <typename T> void List<T>::traverse(void (*visit) (T&))
{
    for(ListNode<T>* p = this->header->next; p != trailer; p = p->next){
        visit(p->data);
    }
}

template <typename T> template <typename VST>
void List<T>::traverse(VST& visit)
{
    for(ListNode<T>* p = this->header->next; p != trailer; p = p->next){
        visit(p->data);
    }
}

template <typename T>
void visit(T data)
{
    std::cout<<"visit data: "<<data<<std::endl;
}
/*
template <typename T>
struct visit{
    public:
    void operator()(T data){
        std::cout<<"op visit data: "<<data<<std::endl;
    }
};
*/

template <typename T> void List<T>::uniquity()
{
    if(_size < 2) return;
    for(ListNode<T>* p = header->next; p != trailer; p = p->next){
        if(p->data == p->next->data){
            remove(p->next);
            p = p->prev;
        }
    }
}

template <typename T> void List<T>::interationSort()
{
    //visit node from second to last
    //find the target node that not greater than current node
    //insert it as next
    //remove current node.
    //switch to next node until last node.
    int i=1;
    ListNode<T>* p = header->next->next;
    for(i = 1; i < this->size(); i++){
        ListNode<T>* node_less_than_p = search(p->data, i, p);
        insertAsSucc(node_less_than_p, p->data);
        p = p->next;
        remove(p->prev);
    }
}

template <typename T> void List<T>::selectionSort()
{
    //a list is devided to header list and trailer list
    //find max node in header list
    //remove max node in header list
    //insert max node in trailer list
    //iterator from n-th node to 1-th node

    //how to find the max node. compare a tmp node with all nodes.
    //if one node greate than the tmp node, tmp node pointer to it.
    ListNode<T> *maxnode = header->next;
    ListNode<T> *lt = header->next;
    ListNode<T> *lastnode = trailer;
    while(lastnode != header->next){
        maxnode = header->next;//be careful, maxnode has been remove and need reset.
        for(lt = header->next; lt != lastnode;lt = lt->next){
            //std::cout<<"lt is "<< lt<<" and its data: "<<lt->data<<std::endl;
            if(lt->data > maxnode->data) maxnode = lt;
        }

        lastnode = insertAsPrev(lastnode, maxnode->data);
        //std::cout<<"before remove ops. traverse list:";
        //traverse();
        remove(maxnode);
        //std::cout<<"after remove ops. traverse list:";
        //traverse();
    }
}

template <typename T> ListNode<T>* selectMax(ListNode<T>* p, int n)
{
    int i = 0;
    ListNode<T> *max = p; 
    ListNode<T> *lt = p;
    for(i = 0; i < n; i++){
        if(lt->data > max->data) max = lt;
        lt = lt->next;
    }
    return max;
}
//sort n nodes starting from node p.
template <typename T> void List<T>::selectionSort_2(ListNode<T>* p, int n)
{
    ListNode<T> *tail = p;
    //if p is removed, then p pointer would be invalid. so store it by header.
    ListNode<T> *head = p->prev;//header and trailer are to avoid boundary cases.
    int i = 0;
    for(i = 0; i < n; i++) {
        tail = tail->next;
    }
    std::cout<<"** Selection sort_2. Initial traverse list:";
    printf("\n");   //vscode bug. so replace std::endl by printf
    traverse();
    while(n > 1)
    {
        ListNode<T> *max = selectMax(head->next, n);
        tail = insertAsPrev(tail, max->data);
        //std::cout<<"max: "<<max<<" data:"<<max->data<<" tail: "<<tail;
        //printf("\n");
        remove(max);
        std::cout<<"Updating one round:";
        printf("\n");
        traverse();
        n--;//if while(n-- > 1), selectMax n would be wrong
    }
    std::cout<<"** Selection sort_2. Updated traverse list:";
    printf("\n");
    traverse();
}

void testBasicOperations();
void testInsertionSort();
void testSelectionSort();
void testSelectionSort();
void testSelectionSort_2();
void testDeduplication();
void testUniquition();

int main(){
    testBasicOperations();
    testInsertionSort();
    testSelectionSort();
    testSelectionSort_2();
    testDeduplication();
    testUniquition();
    return 0;
}

void testBasicOperations()
{
    List<string> *phones = new List<string>();

    //insert node
    phones->insertAsFirst("Huawei phone");
    ListNode<string> *lv = phones->insertAsLast("Lenovo phone");
    phones->insertAsPrev(lv, "Honor phone");
    phones->traverse();

    //find target phone
    ListNode<string> *targetnode = phones->find("Honor phone");
    
    //construct phone with copy mode
    List<string> *copyphones = new List<string>(phones);
    
    //the remove op below is banned and wrong.
    //targetnode is from phones, not copyphones, delete it actually from phones
    //moreover, _size in phones is NOT decreased.

    //copyphones->remove(targetnode);

    //delete Honor phone from copyphones list
    targetnode = copyphones->find("Honor phone");
    copyphones->remove(targetnode);

    //test for deduplate ops
    phones->insertAsPrev(lv, "Honor phone");
    phones->insertAsPrev(lv, "Honor phone");
    phones->deduplicate();

    phones->traverse(visit);

    delete phones;
    delete copyphones;
}

void testInsertionSort()
{
   //build scores list
   //initial scores: 75 80 85 90 70 70 92 95 80 99
   //sorted scores: 70 70 75 80 80 85 90 92 95 99
    List<int> *scorelist = new List<int>();
    ListNode<int> *sl = scorelist->insertAsFirst(75);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 85);
    sl = scorelist->insertAsSucc(sl, 90);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 92);
    sl = scorelist->insertAsSucc(sl, 95);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 99);
    scorelist->traverse();
    //ListNode<int>* sl_80 = scorelist->search(81, 3, sl);
    //std::cout<<"In scorelist, the last node that not greater than 81 is "<<sl_80<<
    //    " and its data is "<<sl_80->data<<std::endl;
    scorelist->interationSort();
    scorelist->traverse();
    delete scorelist;
}

void testSelectionSort()
{
   //build scores list
   //initial scores: 75 80 85 90 70 70 92 95 80 99
   //sorted scores: 70 70 75 80 80 85 90 92 95 99
    List<int> *scorelist = new List<int>();
    ListNode<int> *sl = scorelist->insertAsFirst(75);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 85);
    sl = scorelist->insertAsSucc(sl, 90);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 92);
    sl = scorelist->insertAsSucc(sl, 95);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 99);
    scorelist->traverse();
    //ListNode<int>* sl_80 = scorelist->search(81, 3, sl);
    //std::cout<<"In scorelist, the last node that not greater than 81 is "<<sl_80<<
    //    " and its data is "<<sl_80->data<<std::endl;
    scorelist->selectionSort();
    scorelist->traverse();
    delete scorelist;
}

void testSelectionSort_2()
{
   //build scores list
   //initial scores: 75 80 85 90 70 70 92 95 80 99
   //sorted scores: 70 70 75 80 80 85 90 92 95 99
    List<int> *scorelist = new List<int>();
    ListNode<int> *firstnode;
    ListNode<int> *sl = firstnode = scorelist->insertAsFirst(75);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 85);
    sl = scorelist->insertAsSucc(sl, 90);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 92);
    sl = scorelist->insertAsSucc(sl, 95);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 99);
    scorelist->traverse();
    //ListNode<int>* sl_80 = scorelist->search(81, 3, sl);
    //std::cout<<"In scorelist, the last node that not greater than 81 is "<<sl_80<<
    //    " and its data is "<<sl_80->data<<std::endl;
    scorelist->selectionSort_2(firstnode, 10);
    scorelist->traverse();
    delete scorelist;
}
void testDeduplication()
{
   //build scores list
   //initial scores: 75 80 85 90 70 70 92 95 80 99
   //deduplicated scores: 75 85 90 70 92 95 80 99
    List<int> *scorelist = new List<int>();
    ListNode<int> *sl = scorelist->insertAsFirst(75);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 85);
    sl = scorelist->insertAsSucc(sl, 90);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 70);
    sl = scorelist->insertAsSucc(sl, 92);
    sl = scorelist->insertAsSucc(sl, 95);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 99);
    std::cout<<"Initial scorelist: "<<std::endl;
    scorelist->traverse();
    scorelist->deduplicate();
    std::cout<<"Deduplicated scorelist: "<<std::endl;
    scorelist->traverse();
    delete scorelist;
}
void testUniquition()
{
   //build scores list
   //initial scores: 80 80 85 86 86 90 95 96 96 100
   //deduplicated scores: 80 85 86 90 95 96 100
    List<int> *scorelist = new List<int>();
    ListNode<int> *sl = scorelist->insertAsFirst(80);
    sl = scorelist->insertAsSucc(sl, 80);
    sl = scorelist->insertAsSucc(sl, 85);
    sl = scorelist->insertAsSucc(sl, 86);
    sl = scorelist->insertAsSucc(sl, 86);
    sl = scorelist->insertAsSucc(sl, 90);
    sl = scorelist->insertAsSucc(sl, 95);
    sl = scorelist->insertAsSucc(sl, 96);
    sl = scorelist->insertAsSucc(sl, 96);
    sl = scorelist->insertAsSucc(sl, 100);
    std::cout<<"Initial scorelist: "<<std::endl;
    scorelist->traverse();
    scorelist->uniquity();
    std::cout<<"Uniquity scorelist: "<<std::endl;
    scorelist->traverse();
    delete scorelist;
}