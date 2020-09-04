#include <iostream>
#include <string>
#include <vector>
#include <stack>

template <typename T> struct BinNode {
    T data;
    BinNode<T>* parent;
    BinNode<T>* left;
    BinNode<T>* right;
    int height;
    BinNode() : parent(nullptr), left(nullptr), right(nullptr), height(0) {}
    BinNode(T e, BinNode<T>* p = nullptr, BinNode<T>* left = nullptr, BinNode<T>* right = nullptr, int height = 0)
    : data(e), parent(p), left(left), right(right),height(height){}
    //ops
    //int size();
    BinNode<T>* insertAsLeft(T const&);
    BinNode<T>* insertAsRight(T const&);
    //BinNode<T>* succ();
    template <typename VST> void travPre(VST&);
    template <typename VST> void travIn(VST&);
    template <typename VST> void travPost(VST&);
};

template <typename T> class BinTree{
protected:
    int _size;
    BinNode<T>* _root;
public:
    BinTree():_size(0), _root(nullptr) {}
    ~BinTree(){}
    int size() {return _size;}
    bool empty(){return !_root;}
    BinNode<T>* root() const {return _root;}
    BinNode<T>* insertAsRoot(T const& e);
    BinNode<T>* insertAsLeft(BinNode<T>* x, T const& e);
    BinNode<T>* insertAsRight(BinNode<T>* x, T const& e);
    BinNode<T>* attachAsLeft(BinNode<T>* x, BinTree<T>* lc);
    BinNode<T>* attachAsRight(BinNode<T>* x, BinTree<T>* rc);
    template <typename VST> void travPre(VST& visit) {if(_root) _root->travPre(visit);}
    template <typename VST> void travIn(VST& visit) {if(_root) _root->travIn(visit);}
    template <typename VST> void travPost(VST& visit) {if(_root) _root->travPost(visit);}
};
